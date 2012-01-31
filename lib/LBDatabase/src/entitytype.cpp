#include "entitytype.h"

#include "attribute.h"
#include "column.h"
#include "context.h"
#include "database.h"
#include "entity.h"
#include "function.h"
#include "property.h"
#include "propertyvalue.h"
#include "relation.h"
#include "row.h"
#include "storage.h"
#include "table.h"

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** EntityTypePrivate
*/
//! \cond PRIVATE
const QString EntityType::ContextColumn("context");
const QString EntityType::IdentifierColumn("identifier");
const QString EntityType::ParentEntityTypeColumn("parentEntityType");
const QString EntityType::DisplayNameColumn("displayName");
const QString EntityType::DisplayNamePluralColumn("displayNamePlural");
//! \endcond

class EntityTypePrivate {
    EntityTypePrivate() : context(0), parentEntityType(0), calculator(0) {}

    static QString typeToSql(Attribute::Type type);

    void init();
    void inheritProperties(EntityType *parent);
    void inheritCalculator(EntityType *parent);
    Attribute *addAttribute(const QString &identifier, Attribute::Type type);
    Relation *addRelation(const QString &identifier, EntityType *otherType, Relation::Cardinality cardinality);

    Row *row;
    QString identifier;
    QString displayName;
    QString displayNamePlural;
    Context *context;
    Storage *storage;
    EntityType *parentEntityType;
    int parentEntityTypeId;

    QList<EntityType *> childEntityTypes;

    QHash<QString, Property *> propertiesByName;

    QList<Property *> properties;
    QList<Attribute *> attributes;
    QList<Relation *> relations;
    QList<Entity *> entities;
    QList<Function *> functions;

    Calculator *calculator;

    EntityType * q_ptr;
    Q_DECLARE_PUBLIC(EntityType)
};

QString EntityTypePrivate::typeToSql(Attribute::Type type)
{
    switch(type) {
    case Attribute::Text:
        return Column::typeToName(Column::Text);
    case Attribute::Integer:
        return Column::typeToName(Column::Integer);
    case Attribute::Real:
        return Column::typeToName(Column::Real);
    case Attribute::Unkown:
    default:
        return Column::typeToName(Column::Blob);
    }
}

void EntityTypePrivate::init()
{
    Q_Q(EntityType);
    identifier = row->data(EntityType::IdentifierColumn).toString();
    displayName = row->data(EntityType::DisplayNameColumn).toString();
    displayNamePlural = row->data(EntityType::DisplayNamePluralColumn).toString();
    parentEntityTypeId = row->data(EntityType::ParentEntityTypeColumn).toInt();
    int contextId = row->data(EntityType::ContextColumn).toInt();
    context = storage->context(contextId);
    if(!context) {
        qWarning() << "No such context:" << contextId << "for entity type" << identifier;
        return;
    }
    context->addEntityType(q);
}

void EntityTypePrivate::inheritProperties(EntityType *parent)
{
    Q_Q(EntityType);

    QList<Relation *> newRelations = parent->relations();
    QList<Attribute *> newAttributes = parent->attributes();
    QList<Function *> newFunctions = parent->functions();

    properties.reserve(newAttributes.size() + newRelations.size() + newFunctions.size());
    attributes.reserve(newAttributes.size());
    relations.reserve(newRelations.size());
    functions.reserve(newFunctions.size());

    foreach(Attribute *attribute, newAttributes) {
        properties.append(attribute);
        propertiesByName.insert(attribute->name(), attribute);
    }
    foreach(Relation *relation, newRelations) {
        properties.append(relation);
        propertiesByName.insert(relation->name(), relation);
    }
    foreach(Function *function, newFunctions) {
        properties.append(function);
        propertiesByName.insert(function->name(), function);
    }

    relations.append(newRelations);
    attributes.append(newAttributes);
    functions.append(newFunctions);

    foreach(EntityType *type, childEntityTypes) {
        type->d_func()->inheritProperties(q);
    }
}

void EntityTypePrivate::inheritCalculator(EntityType *parent)
{
    Q_Q(EntityType);
    if(!calculator)
        calculator = parent->calculator();

    foreach(EntityType *type, childEntityTypes) {
        type->d_func()->inheritCalculator(q);
    }
}

Attribute *EntityTypePrivate::addAttribute(const QString &name, Attribute::Type type)
{
    Table *contextTable = storage->database()->table(context->identifier());
    contextTable->addColumn(name, EntityTypePrivate::typeToSql(type));

    Table *entitiesTable = storage->attributesTable();
    Row *row = entitiesTable->appendRow();
    row->setData(Attribute::NameColumn, QVariant(name));
    row->setData(Attribute::DisplayNameColumn, QVariant(name));
    row->setData(Attribute::EntityTypeIdColumn, QVariant(this->row->id()));

    Attribute *attribute = new Attribute(row, storage);
    storage->insertAttribute(attribute);
    attribute->addPropertyValueToEntities();
    foreach(Entity *entity, entities) {
        entity->propertyValue(attribute)->fetchValue();
    }

    return attribute;
}

Relation *EntityTypePrivate::addRelation(const QString &name, EntityType *otherType, Relation::Cardinality cardinality)
{
    Q_Q(EntityType);
    Row *row = storage->contextsTable()->appendRow();
    row->setData(Relation::NameColumn, QVariant(name));
    row->setData(Relation::EntityTypeLeftColumn, QVariant(q->id()));
    row->setData(Relation::EntityTypeRightColumn, QVariant(otherType->id()));
    row->setData(Relation::DisplayNameLeftColumn, QVariant(name));
    row->setData(Relation::DisplayNameRightColumn, QVariant(name));
    row->setData(Relation::CardinalityColumn, QVariant(static_cast<int>(cardinality)));

    if(cardinality == Relation::OneToMany || cardinality == Relation::OneToOne) {
        storage->database()->table(otherType->identifier())->addColumn(name, Column::typeToName(Column::Integer));
    }
    else if(cardinality == Relation::ManyToMany) {
        Table *table = storage->database()->createTable(name);
        table->addColumn(q->identifier(), Column::typeToName(Column::Integer));
        table->addColumn(otherType->identifier(), Column::typeToName(Column::Integer));
    }

    Relation *relation = new Relation(row, storage);
    storage->insertRelation(relation);
    relation->addPropertyValueToEntities();
    foreach(Entity *entity, entities) {
        entity->propertyValue(relation)->fetchValue();
    }

    return relation;
}

/******************************************************************************
** EntityType
*/
/*!
  \class EntityType
  \brief The EntityType class represents a description of a type of entities.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var EntityType::d_ptr
  \internal
  */

/*!
  \fn EntityType::nameChanged(QString name)

  This signal is emitted, when the name of the entity type changes.
  */

/*!
  Creates a new entity type, which represents the type described in \a row in
  the Storage \a parent.
  */
EntityType::EntityType(Row *row, Storage *parent) :
    QObject(parent),
    d_ptr(new EntityTypePrivate)
{
    Q_D(EntityType);
    d->q_ptr = this;
    d->row = row;
    d->storage = parent;
    d->init();
}

/*!
  Destroys the type.
  */
EntityType::~EntityType()
{
}

/*!
  Returns the storage-global id of the type.
  */
int EntityType::id() const
{
    Q_D(const EntityType);
    return d->row->id();
}

/*!
  Returns the name of the type.
  */
QString EntityType::identifier() const
{
    Q_D(const EntityType);
    return d->identifier;
}

/*!
  Sets the name of the type to \a name.
  */
void EntityType::setIdentifier(const QString &identifier)
{
    Q_D(EntityType);
    if(d->identifier == identifier)
        return;

    d->row->setData(EntityType::IdentifierColumn, QVariant(identifier));
    d->identifier = identifier;
    emit identifierChanged(identifier);
}

QString EntityType::displayName() const
{
    Q_D(const EntityType);
    return d->displayName;
}

void EntityType::setDisplayName(const QString &displayName)
{
    Q_D(EntityType);
    if(d->displayName == displayName)
        return;

    d->row->setData(EntityType::DisplayNameColumn, QVariant(displayName));
    d->displayName = displayName;
    emit displayNameChanged(displayName);
}

QString EntityType::displayNamePlural() const
{
    Q_D(const EntityType);
    return d->displayNamePlural;
}

void EntityType::setDisplayNamePlural(const QString &displayNamePlural)
{
    Q_D(EntityType);
    if(d->displayNamePlural == displayNamePlural)
        return;

    d->row->setData(EntityType::DisplayNamePluralColumn, QVariant(displayNamePlural));
    d->displayNamePlural = displayNamePlural;
    emit displayNameChanged(displayNamePlural);
}

/*!
  Returns the context to which the type belongs.
  */
LBDatabase::Context *EntityType::context() const
{
    Q_D(const EntityType);
    return d->context;
}

/*!
  Returns the type, from which this type inherits its properties or \a 0 if this
  type is the base type of its Context.
  */
EntityType *EntityType::parentEntityType() const
{
    Q_D(const EntityType);
    return d->parentEntityType;
}

/*!
  \internal

  Sets the Context to \a context. This is done when loading the storage.
  */
void EntityType::setContext(LBDatabase::Context *context)
{
    Q_D(EntityType);
    if(d->context == context)
        return;
    d->context = context;
}

/*!
  \internal

  Adds a type, which inherits this type. This is done when loading the storage.
  */
void EntityType::addChildEntityType(EntityType *type)
{
    Q_D(EntityType);
    if(d->childEntityTypes.contains(type))
        return;

    d->childEntityTypes.append(type);
}

/*!
  \internal

  Sets the type from which this type inherits its properties. This is done when
  loading the storage.
  */
void EntityType::setParentEntityType(EntityType *type)
{
    Q_D(EntityType);
    if(d->parentEntityType == type)
        return;
    d->parentEntityType = type;
}

/*!
  \internal

  Returns the ID of the parent type. This is used when loading the storage.
  */
int EntityType::parentEntityTypeId() const
{
    Q_D(const EntityType);
    return d->parentEntityTypeId;
}

/*!
  Returns the list of types, which are derived from the type.
  */
QList<EntityType *> EntityType::childEntityTypes() const
{
    Q_D(const EntityType);
    return d->childEntityTypes;
}

Property *EntityType::property(const QString &name) const
{
    Q_D(const EntityType);
    return d->propertiesByName.value(name, 0);
}

/*!
  Returns the list of properties of the type.

  This includes all attributes and relations.
  */
QList<Property *> EntityType::properties() const
{
    Q_D(const EntityType);
    return d->properties;
}

/*!
  Returns the list of attributes of the type.
  */
QList<Attribute *> EntityType::attributes() const
{
    Q_D(const EntityType);
    return d->attributes;
}

/*!
  Returns the list of relations of the type.
  */
QList<Relation *> EntityType::relations() const
{
    Q_D(const EntityType);
    return d->relations;
}

QList<Function *> EntityType::functions() const
{
    Q_D(const EntityType);
    return d->functions;
}

QList<Property *> EntityType::nonInhertitedProperties() const
{
    QList<Property *> list = properties();
    if(parentEntityType()) {
        foreach(Property *property, parentEntityType()->properties()) {
            list.removeAll(property);
        }
    }
    return list;
}

QList<Attribute *> EntityType::nonInhertitedAttributes() const
{
    QList<Attribute *> list = attributes();
    if(parentEntityType()) {
        foreach(Attribute *attribute, parentEntityType()->attributes()) {
            list.removeAll(attribute);
        }
    }
    return list;
}

QList<Relation *> EntityType::nonInhertitedRelations() const
{
    QList<Relation *> list = relations();
    if(parentEntityType()) {
        foreach(Relation *relation, parentEntityType()->relations()) {
            list.removeAll(relation);
        }
    }
    return list;
}

QList<Function *> EntityType::nonInhertitedFunctions() const
{
    QList<Function *> list = functions();
    if(parentEntityType()) {
        foreach(Function *function, parentEntityType()->functions()) {
            if(!function->reimplementingEntityTypes().contains(const_cast<EntityType*>(this)))
                list.removeAll(function);
        }
    }
    return list;
}

/*!
  Adds a new attribute with the name \a name and the type \a type to the type.
  */
Attribute *EntityType::addAttribute(const QString &name, Attribute::Type type)
{
    Q_D(EntityType);
    return d->addAttribute(name, type);
}

/*!
  Adds a new relation with the name \a name, which will map to entities of type
  \a otherType and has the cardinality \a cardinality.
  */
Relation *EntityType::addRelation(const QString &name, EntityType *otherType, Relation::Cardinality cardinality)
{
    Q_D(EntityType);
    return d->addRelation(name, otherType, cardinality);
}

/*!
  Returns a list of all entites of the type. This includes all entities of
  types, which inherit this type.
  */
QList<Entity *> EntityType::entities() const
{
    Q_D(const EntityType);
    return d->entities;
}

/*!
  Returns true, if the given \a entityType inherits or is equal to this type.
  This means, that the given type has at least the properties of this type.
  */
bool EntityType::inherits(EntityType *entityType) const
{
    Q_D(const EntityType);

    if(d->parentEntityType == entityType || this == entityType)
        return true;

    if(!d->parentEntityType || !entityType)
        return false;

    return d->parentEntityType->inherits(entityType);
}

Calculator *EntityType::calculator() const
{
    Q_D(const EntityType);
    return d->calculator;
}

/*!
  \internal

  Adds \a attribute to the attributes of this type. This is used when loading the storage.
  */
void EntityType::addAttribute(Attribute *attribute)
{
    Q_D(EntityType);
    d->properties.append(attribute);
    d->propertiesByName.insert(attribute->name(), attribute);
    d->attributes.append(attribute);
}

/*!
  \internal

  Adds \a relation to the relations of this type. This is used when loading the storage.
  */
void EntityType::addRelation(Relation *relation)
{
    Q_D(EntityType);
    d->properties.append(relation);
    d->propertiesByName.insert(relation->name(), relation);
    d->relations.append(relation);
}

void EntityType::addFunction(Function *function)
{
    Q_D(EntityType);
    d->properties.append(function);
    d->propertiesByName.insert(function->name(), function);
    d->functions.append(function);
}

/*!
  \internal

  Adds the properties of \a parent to this entity.
  */
void EntityType::inheritProperties(EntityType *parent)
{
    Q_D(EntityType);
    d->inheritProperties(parent);
}

void EntityType::inheritCalculator(EntityType *parent)
{
    Q_D(EntityType);
    d->inheritCalculator(parent);
}

/*!
  \internal

  Adds \a entity to the list of all entities of this type and each type it is
  derived from.
  */
void EntityType::addEntity(Entity *entity)
{
    Q_D(EntityType);
    d->entities.append(entity);
    if(d->parentEntityType)
        d->parentEntityType->addEntity(entity);
}

void EntityType::setCalculator(Calculator *calculator)
{
    Q_D(EntityType);
    d->calculator = calculator;
}

} // namespace LBDatabase
