#include "context.h"

#include "attribute.h"
#include "attributevalue.h"
#include "calculator.h"
#include "database.h"
#include "entity.h"
#include "entitytype.h"
#include "function.h"
#include "relation.h"
#include "row.h"
#include "storage.h"
#include "table.h"

#include <QHash>
#include <QList>
#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** ContextPrivate
*/
//! \cond PRIVATE
const QString Context::IdentifierColumn("identifier");
const QString Context::DisplayNameColumn("displayName");
const QString Context::TableNameColumn("tableName");
//! \endcond

class ContextPrivate {
    ContextPrivate() : baseEntityType(0) {}

    void init();
    void initializeEntityHierarchy();
    void loadEntities();
    void initializeRelations();
    void fillRelations();
    void createBaseEntityType(const QString &identifier);

    EntityType *addEntityType(const QString &identifier, EntityType *parentEntityType);
    Entity *insertEntity(EntityType *type);

    Entity *createEntityInstance(Row *row);
    Calculator *createCalculatorInstance(const QString &entityTypeName);

    Row *row;
    Storage *storage;
    QString identifier;
    QString displayName;
    QList<EntityType *> entityTypes;
    EntityType *baseEntityType;
    Table *contextTable;
    QList<Entity *> entities;
    QHash<int, Entity *> entitiesById;
    QList<Property *> properties;

    QHash<QString, QMetaObject> entityMetaObjects;
    QHash<QString, QMetaObject> calculatorMetaObjects;

    Context * q_ptr;
    Q_DECLARE_PUBLIC(Context)
};

void ContextPrivate::init()
{
    identifier = row->data(Context::IdentifierColumn).toString();
    displayName = row->data(Context::DisplayNameColumn).toString();
    contextTable = storage->database()->table(row->data(Context::TableNameColumn).toString());

    if(!contextTable)
        qWarning() << "No such table" << row->data(Context::TableNameColumn).toString() << "for context" << identifier << "(ID" << row->id() << ")";
}

void ContextPrivate::initializeEntityHierarchy()
{
    EntityType *parentType;
    foreach(EntityType *type, entityTypes) {

        parentType = storage->entityType(type->parentEntityTypeId());
        if(parentType) {
            type->setParentEntityType(parentType);
            parentType->addChildEntityType(type);
        }
        else {
            baseEntityType = type;
        }
    }
    foreach(EntityType *type, entityTypes) {
        type->setCalculator(createCalculatorInstance(type->identifier()));
    }

    foreach(EntityType *child, baseEntityType->childEntityTypes()) {
        child->inheritProperties(baseEntityType);
        child->inheritCalculator(baseEntityType);
    }
}

void ContextPrivate::loadEntities()
{
    if(!contextTable)
        return;

    entities.reserve(contextTable->rows().size());
    entitiesById.reserve(contextTable->rows().size());
    foreach(Row *row, contextTable->rows()) {
        Entity *entity = createEntityInstance(row);
        entities.append(entity);
        entitiesById.insert(row->id(), entity);
    }
}

EntityType *ContextPrivate::addEntityType(const QString &name, EntityType *parentEntityType)
{
    Row *entityTypeRow = storage->entityTypesTable()->appendRow();
    entityTypeRow->setData(EntityType::IdentifierColumn, QVariant(name));
    entityTypeRow->setData(EntityType::ParentEntityTypeColumn, QVariant(parentEntityType->id()));
    entityTypeRow->setData(EntityType::ContextColumn, QVariant(row->id()));

    EntityType *type = new EntityType(entityTypeRow, storage);
    type->setParentEntityType(parentEntityType);
    parentEntityType->addChildEntityType(type);
    storage->insertEntityType(type);

    type->inheritProperties(parentEntityType);
    return type;
}

Entity *ContextPrivate::insertEntity(EntityType *type)
{
    Q_Q(Context);
    Row *row = contextTable->appendRow();
    row->setData(Entity::EntityTypeIdColumn, QVariant(type->id()));

    q->beginInsertRows(QModelIndex(), entities.size(), entities.size());
    Entity *entity =  createEntityInstance(row);
    entities.append(entity);
    entitiesById.insert(row->id(), entity);

    foreach(Property *property, type->properties()) {
        property->addPropertyValue(entity);
    }
    foreach(PropertyValue *value, entity->propertyValues()) {
        value->fetchValue();
    }
    q->endInsertRows();

    return entity;
}

void ContextPrivate::createBaseEntityType(const QString &name)
{
    Row *entityTypeRow = storage->entityTypesTable()->appendRow();
    entityTypeRow->setData(EntityType::IdentifierColumn, QVariant(name));
    entityTypeRow->setData(EntityType::ParentEntityTypeColumn, QVariant());
    entityTypeRow->setData(EntityType::ContextColumn, QVariant(row->id()));

    baseEntityType = new EntityType(entityTypeRow, storage);
    storage->insertEntityType(baseEntityType);
}

Entity *ContextPrivate::createEntityInstance(Row *row)
{
    Q_Q(Context);
    int typeId = row->data(Entity::EntityTypeIdColumn).toInt();
    EntityType *type = storage->entityType(typeId);
    QString entityTypeName = type->identifier();

    while(!entityMetaObjects.contains(entityTypeName)) {
        type = type->parentEntityType();
        if(!type)
            break;

        entityTypeName = type->identifier();
    }

    if(!entityMetaObjects.contains(entityTypeName))
        return new Entity(row, q);

    QObject *object = entityMetaObjects.value(entityTypeName).newInstance(Q_ARG(::LBDatabase::Row*,row), Q_ARG(::LBDatabase::Context*, q));
    return static_cast<Entity *>(object);
}

Calculator *ContextPrivate::createCalculatorInstance(const QString &entityTypeName)
{
    Q_Q(Context);
    if(!calculatorMetaObjects.contains(entityTypeName))
        return 0;

    QObject *object = calculatorMetaObjects.value(entityTypeName).newInstance(Q_ARG(QObject*, q));
    return static_cast<Calculator *>(object);
}


/******************************************************************************
** Context
*/
/*!
  \class Context
  \brief The Context class represents a context in a Storage.

  \ingroup highlevel-database-classes

  Each context is responsible for a hierarchy of EntityType and the concrete
  Entity instances of these types. It always has exactly one baseEntityType()
  from which other types in the context may be derived. The entityTypes() list
  contains every type in the context. You can add a new type with
  addEntityType().

  You may access the Entity instances of each context either by id (entity()),
  by index (entityAt()) or through the list of all entities(). You can insert
  new entities into the context by calling insertEntity().

  The Context class inherits QAbstractTableModel, so that you can add it as a
  model for any model-view based Qt class like QTreeView. This model is
  editable.

  */
/*!
  \fn Context::nameChanged(QString name)

  This signal is emitted when the name of this context changes.

  */

/*!
  \var Context::d_ptr
  \internal
  */

/*!
  Creates a new context in the Storage \a parent, which is described by /a row.
  */
Context::Context(Row *row, Storage *parent) :
    QAbstractTableModel(parent),
    d_ptr(new ContextPrivate)
{
    Q_D(Context);
    d->q_ptr = this;
    d->row = row;
    d->storage = parent;
    d->init();
}

/*!
  Destroys the context.
  */
Context::~Context()
{
}

/*!
  Returns the storage-global ID of the context.
  */
int Context::id() const
{
    Q_D(const Context);
    return d->row->id();
}

/*!
  Returns the name of the context. This name is also the name of the Sqlite
  table, which contains the Entity instances of the context.
  */
QString Context::identifier() const
{
    Q_D(const Context);
    return d->identifier;
}

QString Context::displayName() const
{
    Q_D(const Context);
    return d->displayName;
}

/*!
  Returns the storage, which contains the context.
  */
Storage *Context::storage() const
{
    Q_D(const Context);
    return d->storage;
}

/*!
  Returns the table, that contains the entities in this context.
  */
Table *Context::table() const
{
    Q_D(const Context);
    return d->contextTable;
}

/*!
  Returns the EntityType, from which all types in the context are somehow
  derived.
  */
EntityType *Context::baseEntityType() const
{
    Q_D(const Context);
    return d->baseEntityType;
}

/*!
  Returns a list of all types, for which the context is responsible.
  */
QList<EntityType *> Context::entityTypes() const
{
    Q_D(const Context);
    return d->entityTypes;
}

/*!
  Adds a new EntityType to the context, which will inherit all properties from
  \a parentEntityType.
  */
EntityType *Context::addEntityType(const QString &name, EntityType *parentEntityType)
{
    Q_D(Context);
    return d->addEntityType(name, parentEntityType);
}

/*!
  Returns the Entity instance with the ID \a id.
  */
Entity *Context::entity(int id) const
{
    Q_D(const Context);
    return d->entitiesById.value(id);
}

/*!
  Returns a list of all Entity instances.
  */
QList<Entity *> Context::entities() const
{
    Q_D(const Context);
    return d->entities;
}

/*!
  Inserts a new Entity of the type \a type into the context and returns the
  instance.
  */
Entity *Context::insertEntity(EntityType *type)
{
    Q_D(Context);
    return d->insertEntity(type);
}

/*!
  \internal

  Creates the base entity type for the context. This is only being used, when
  creating a new context.
  */
void Context::createBaseEntityType(const QString &name)
{
    Q_D(Context);
    d->createBaseEntityType(name);
}

/*!
  \internal

  Adds the EntityType \a type to the context. This is when loading the storage.
  */
void Context::addEntityType(EntityType *type)
{
    Q_D(Context);
    if(d->entityTypes.contains(type))
        return;

    connect(type, SIGNAL(displayNameChanged(QString)), this, SLOT(onEntityTypeNameChanged(QString)));
    d->entityTypes.append(type);
}

/*!
  \internal

  Adds the Attribute \a attribute to the context. This is when loading the storage.
  */
void Context::addAttribute(Attribute *attribute)
{
    Q_D(Context);
    if(d->properties.contains(attribute))
        return;

    beginInsertColumns(QModelIndex(), d->properties.size(), d->properties.size());
    d->properties.append(attribute);
    connect(attribute, SIGNAL(displayNameChanged(QString,Context*)), this, SLOT(onPropertyDisplayNameChanged(QString,Context*)));
    endInsertColumns();
}

void Context::addFunction(Function *function)
{
    Q_D(Context);
    if(d->properties.contains(function))
        return;

    beginInsertColumns(QModelIndex(), d->properties.size(), d->properties.size());
    d->properties.append(function);
    connect(function, SIGNAL(displayNameChanged(QString,Context*)), this, SLOT(onPropertyDisplayNameChanged(QString,Context*)));
    endInsertColumns();
}

/*!
  \internal

  Adds the Relation \a relation to the context. This is when loading the storage.
  */
void Context::addRelation(Relation *relation)
{
    Q_D(Context);
    if(d->properties.contains(relation))
        return;

    beginInsertColumns(QModelIndex(), d->properties.size(), d->properties.size());
    d->properties.append(relation);
    connect(relation, SIGNAL(displayNameChanged(QString,Context*)), this, SLOT(onPropertyDisplayNameChanged(QString,Context*)));
    endInsertColumns();
}

/*!
  \internal

  Initialized the hierarchy of the EntityTypes. This is when loading the storage.
  */
void Context::initializeEntityHierarchy()
{
    Q_D(Context);
    d->initializeEntityHierarchy();
}

/*!
  \internal

  Loads the Entity instances in this context. This is when loading the storage.
  */
void Context::loadEntities()
{
    Q_D(Context);
    d->loadEntities();
}

/*!
  Implements QAbstractTableModel::data()
  */
QVariant Context::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        Q_D(const Context);
        Entity *entity = d->entities.at(index.row());
        switch(index.column()) {
        case 0:
            return entity->row()->id();
        case 1:
            return entity->entityType()->displayName();
        default:
            return entity->data(d->properties.at(index.column() - 2));
        }
    }

    return QVariant();
}

/*!
  Implements QAbstractTableModel::headerData()
  */
QVariant Context::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal) {
        if(role == Qt::DisplayRole) {
            Q_D(const Context);
            switch(section) {
            case 0:
                return QLatin1String("ID");
            case 1:
                return QLatin1String("Type");
            default:
                return d->properties.at(section - 2)->displayName(this);
            }
        }
        else if(role == Qt::TextAlignmentRole) {
            return Qt::AlignLeft;
        }
    }
    return QVariant();
}

/*!
  Implements QAbstractTableModel::columnCount()
  */
int Context::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }
    Q_D(const Context);
    return d->properties.size() + 2;
}

/*!
  Implements QAbstractTableModel::rowCount()
  */
int Context::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }
    Q_D(const Context);
    return d->entities.size();
}

/*!
  \internal
  Listens to name changes of EntityTypes and updates the model accordingly.
  */
void Context::onEntityTypeNameChanged(QString name)
{
    Q_D(const Context);
    Q_UNUSED(name);
    EntityType *type = static_cast<EntityType *>(sender());
    QModelIndex i = index(d->entityTypes.indexOf(type), 1);
    emit dataChanged(i, i);
}

/*!
  \internal
  Listens to name changes of Properties and updates the model accordingly.
  */
void Context::onPropertyDisplayNameChanged(QString displayName, Context *context)
{
    Q_D(const Context);
    Q_UNUSED(displayName);
    if(context == this) {
        Property *p = static_cast<Property *>(sender());
        int i =d->properties.indexOf(p);
        emit headerDataChanged(Qt::Horizontal, i, i);
    }
}

/*!
  \internal
  Listens to changes of PropertyValues and updates the model accordingly.
  */
void Context::onPropertyValueDataChanged(QVariant data)
{
    Q_D(const Context);
    Q_UNUSED(data);

    PropertyValue *v = static_cast<PropertyValue *>(sender());
    QModelIndex i = index(d->entities.indexOf(v->entity()), d->properties.indexOf(v->property()));
    emit dataChanged(i, i);
}

/*!
  Implements QAbstractTableModel::setData()
  */
bool Context::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        Q_D(const Context);
        Entity *e = d->entities.at(index.row());
        PropertyValue *v = e->propertyValue(d->properties.value(index.column() - 2));
        if(v)
            return v->setData(value);
    }
    return false;
}

/*!
  Implements QAbstractTableModel::flags()
  */
Qt::ItemFlags Context::flags(const QModelIndex &index) const
{
    Q_D(const Context);
    if(index.column() > 1) {
        Entity *e = d->entities.at(index.row());
        PropertyValue *v = e->propertyValue(d->properties.value(index.column() - 2));
        if(v && v->isEditable()) {
            return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
        }
    }

    return QAbstractItemModel::flags(index);
}

void Context::registerEntityClass(const QString &entityName, QMetaObject metaObject)
{
    Q_D(Context);
    if(d->entityMetaObjects.contains(entityName))
        return;

    d->entityMetaObjects.insert(entityName, metaObject);
}

void Context::registerCalculatorClass(const QString &entityName, QMetaObject metaObject)
{
    Q_D(Context);
    if(d->calculatorMetaObjects.contains(entityName))
        return;

    d->calculatorMetaObjects.insert(entityName, metaObject);
}

} // namespace LBDatabase
