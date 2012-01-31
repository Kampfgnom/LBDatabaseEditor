#include "storage.h"

#include "attribute.h"
#include "column.h"
#include "concreterelation.h"
#include "context.h"
#include "database.h"
#include "entity.h"
#include "entitytype.h"
#include "enumattribute.h"
#include "function.h"
#include "propertyvalue.h"
#include "relation.h"
#include "row.h"
#include "table.h"

#include <QFile>
#include <QMutex>
#include <QFileInfo>

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** StoragePrivate
*/
namespace {
const QString MetaDataTableName("lbmeta");
const QString ContextsTableName("lbmeta_contexts");
const QString EntitiesTableName("lbmeta_entitytypes");
const QString AttributesTableName("lbmeta_attributes");
const QString RelationsTableName("lbmeta_relations");
const QString FunctionsTableName("lbmeta_functions");

const QString NameColumn("name");
const QString SourcePathColumn("cpppath");
}

class StoragePrivate {
    static QHash<QString, Storage*> instances;

    StoragePrivate() : database(0) {}

    void init();
    bool open();
    Context *addContext(const QString &name, const QString &baseEntityTypeName);

    Context *createContextInstance(Row *row);

    Table *attributesTable;
    Table *contextsTable;
    Table *entityTypesTable;
    Table *metaDataTable;
    Table *relationsTable;
    Table *functionsTable;

    QString name;
    QString sourcePath;
    QString fileName;
    Database *database;

    QHash<int, Context *> contexts;
    QHash<QString, int> contextIds;
    QHash<int, EntityType *> entityTypes;
    QHash<int, Attribute *> attributes;
    QHash<int, Relation *> relations;
    QHash<int, Function *> functions;
    QList<Property *> properties;

    QHash<QString, QMetaObject> contextMetaObjects;

    Storage * q_ptr;
    Q_DECLARE_PUBLIC(Storage)
};

QHash<QString, Storage*> StoragePrivate::instances = QHash<QString, Storage*>();

void StoragePrivate::init()
{
    database = Database::instance(fileName);
}

bool sortContextByName(const Context *c1, const Context *c2)
{
    return c1->identifier() < c2->identifier();
}

bool StoragePrivate::open()
{
    Q_Q(Storage);
    if(!database)
        return false;

    QFile file(fileName);
    if(!file.exists()) {
        file.open(QFile::ReadOnly);
        file.close();
    }

    if(!database->open())
        return false;

    metaDataTable = database->table(MetaDataTableName);
    if(!metaDataTable)
        return false;

    contextsTable = database->table(ContextsTableName);
    if(!contextsTable)
        return false;

    entityTypesTable = database->table(EntitiesTableName);
    if(!entityTypesTable)
        return false;

    attributesTable = database->table(AttributesTableName);
    if(!attributesTable)
        return false;

    relationsTable = database->table(RelationsTableName);
    if(!relationsTable)
        return false;

    functionsTable = database->table(FunctionsTableName);
    if(!functionsTable)
        return false;

    Row *metaDataRow = metaDataTable->rowAt(0);
    name = metaDataRow->data(NameColumn).toString();
    sourcePath = metaDataRow->data(SourcePathColumn).toString();

    contexts.reserve(contextsTable->rows().size());
    entityTypes.reserve(entityTypesTable->rows().size());
    attributes.reserve(attributesTable->rows().size());
    properties.reserve(attributesTable->rows().size() + relationsTable->rows().size() + functionsTable->rows().size());

    foreach(Row *row, contextsTable->rows()) {
        Context *context = createContextInstance(row);
        contexts.insert(row->id(), context);
        contextIds.insert(context->identifier(), row->id());
    }

    foreach(Row *row, entityTypesTable->rows()) {
        q->insertEntityType(new EntityType(row, q));
    }

    foreach(Row *row, attributesTable->rows()) {
        if(static_cast<Attribute::Type>(row->data(Attribute::TypeColumn).toInt()) == Attribute::Enum) {
            q->insertAttribute(new EnumAttribute(row, q));
        }
        else {
            q->insertAttribute(new Attribute(row, q));
        }
    }

    foreach(Row *row, database->table(EnumAttribute::EnumsTable)->rows()) {
        EnumAttribute *attribute = static_cast<EnumAttribute *>(attributes.value(row->data(EnumAttribute::AttributeColumn).toInt()));
        attribute->addEnumValue(row->data(EnumAttribute::IdentifierColumn).toString(),
                                row->data(EnumAttribute::ValueColumn).toInt());
    }

    foreach(Row *row, relationsTable->rows()) {
        q->insertRelation(new Relation(row, q));
    }

    foreach(Row *row, functionsTable->rows()) {
        q->insertFunction(new Function(row, q));
    }

    foreach(Row *row, database->table(Function::FunctionReimplementationsTable)->rows()) {
        Function *function = functions.value(row->data(Function::ReimplementedFunctionColumn).toInt());
        EntityType *type = entityTypes.value(row->data(Function::ReimplementingEntityTypeColumn).toInt());
        function->addReimplementingEntityType(type);
    }

    foreach(Context *context, contexts.values()) {
        context->initializeEntityHierarchy();
        context->loadEntities();
    }

    foreach(Property *property, properties) {
        property->addPropertyValueToEntities();
    }
    foreach(Property *property, properties) {
        property->fetchValues();
    }

    return true;
}

Context *StoragePrivate::addContext(const QString &name, const QString &baseEntityTypeName)
{
    database->createTable(name);
    Row *row = contextsTable->appendRow();
    row->setData(Context::IdentifierColumn, QVariant(name));

    Context *context = createContextInstance(row);
    contexts.insert(row->id(), context);

    context->createBaseEntityType(baseEntityTypeName);

    return context;
}

Context *StoragePrivate::createContextInstance(Row *row)
{
    Q_Q(Storage);
    const QString contextName = row->data(Context::IdentifierColumn).toString();

    if(!contextMetaObjects.contains(contextName))
        return new Context(row, q);

    QObject *object = contextMetaObjects.value(contextName).newInstance(Q_ARG(::LBDatabase::Row*,row), Q_ARG(::LBDatabase::Storage*, q));
    return static_cast<Context *>(object);
}

/******************************************************************************
** Storage
*/
/*!
  \class Storage
  \brief The Storage class represents a high level storage for entities.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var Storage::d_ptr
  \internal
  */

/*!
  \fn Storage::nameChanged()

  This signal is emitted when the name of this storage changes.

  */

/*!
  Returns a storage instance, which holds the data contained in the storage file
  \a fileName.

  This will return exactly one instance per file, i.e. you can open each file
  only exactly once.
  */
Storage *Storage::instance(const QString &fileName)
{
    static QMutex mutex(QMutex::Recursive);
    static QObject guard;
    QMutexLocker locker(&mutex);
    Q_UNUSED(locker)

    if(StoragePrivate::instances.contains(fileName)) {
        return StoragePrivate::instances.value(fileName);
    }

    Storage* storage = new Storage(fileName, &guard);
    StoragePrivate::instances.insert(fileName, storage);
    return storage;
}

void Storage::convertSqlliteDatabaseToStorage(const QString &sqliteDatabaseFileName, const QString &storageFileName)
{
    QFile file(sqliteDatabaseFileName);
    file.open(QFile::ReadOnly);
    file.copy(storageFileName);
    file.close();


    Database *database = Database::instance(storageFileName);
    database->open();
    QList<Table *> tables = database->tables();

    database->createTable(MetaDataTableName);
    database->createTable(ContextsTableName);
    database->createTable(EntitiesTableName);
    database->createTable(AttributesTableName);
    database->createTable(RelationsTableName);
    Table *metaDataTable = database->table(MetaDataTableName);
    Table *contextsTable = database->table(ContextsTableName);
    Table *entityTypesTable = database->table(EntitiesTableName);
    Table *attributesTable = database->table(AttributesTableName);
    Table *relationsTable = database->table(RelationsTableName);

    metaDataTable->addColumn(NameColumn,QLatin1String("TEXT"));
    metaDataTable->appendRow();

    contextsTable->addColumn(Context::IdentifierColumn,QLatin1String("TEXT"));

    entityTypesTable->addColumn(EntityType::ContextColumn,QLatin1String("INTERGER"));
    entityTypesTable->addColumn(EntityType::IdentifierColumn,QLatin1String("TEXT"));
    entityTypesTable->addColumn(EntityType::ParentEntityTypeColumn,QLatin1String("INTERGER"));

    attributesTable->addColumn(Attribute::IdentifierColumn,QLatin1String("TEXT"));
    attributesTable->addColumn(Attribute::DisplayNameColumn,QLatin1String("TEXT"));
    attributesTable->addColumn(Attribute::EntityTypeIdColumn,QLatin1String("INTERGER"));

//    relationsTable->addColumn(Relation::NameColumn,QLatin1String("TEXT"));
//    relationsTable->addColumn(Relation::DisplayNameLeftColumn,QLatin1String("TEXT"));
//    relationsTable->addColumn(Relation::DisplayNameRightColumn,QLatin1String("TEXT"));
//    relationsTable->addColumn(Relation::EntityTypeLeftColumn,QLatin1String("INTERGER"));
//    relationsTable->addColumn(Relation::EntityTypeRightColumn,QLatin1String("INTERGER"));
//    relationsTable->addColumn(Relation::CardinalityColumn,QLatin1String("INTERGER"));

    Storage *storage = Storage::instance(storageFileName);
    storage->open();
    storage->setName(QFileInfo(storageFileName).fileName());

    foreach(Table *table, tables) {
        Context *context = storage->addContext(table->name(), table->name().remove(table->name().size() - 1, 1));
        EntityType *base = context->baseEntityType();

        table->addColumn(Entity::EntityTypeIdColumn, QLatin1String("INTEGER"), QVariant(base->id()));

        foreach(Column *column, table->columns()) {
            if(column->name().compare("ID", Qt::CaseInsensitive) != 0) {
                base->addAttribute(column->name(),Attribute::Unkown);
            }
        }
    }
}

/*!
  Closes the storage.
  */
Storage::~Storage()
{
}

/*!
  Returns the database, on which the storage works. Note that changes to the
  database are not automatically reflected in the storage.
  */
Database *Storage::database() const
{
    Q_D(const Storage);
    return d->database;
}

/*!
  Returns the name of the storage.
  */
QString Storage::name() const
{
    Q_D(const Storage);
    return d->name;
}

/*!
  Sets the name of the storage to \a name. Note that this name is not connected
  to the file name, but is stored in the database itself.
  */
void Storage::setName(const QString &name)
{
    Q_D(Storage);
    if(d->name == name)
        return;

    d->metaDataTable->rowAt(0)->setData(NameColumn, QVariant(name));
    d->name = name;
    emit nameChanged(name);
}

/*!
  Creates a storage, which uses the database \a fileName.
  */
Storage::Storage(const QString &fileName, QObject *parent) :
    QObject(parent),
    d_ptr(new StoragePrivate)
{
    Q_D(Storage);
    d->q_ptr = this;
    d->fileName = fileName;
    d->init();
}

/*!
  Returns the file name of the storage.
  */
QString Storage::fileName() const
{
    Q_D(const Storage);
    return d->fileName;
}

QString Storage::sourcePath() const
{
    Q_D(const Storage);
    return d->sourcePath;
}

/*!
  Returns the EntityType with the ID \a id.
  */
EntityType *Storage::entityType(int id) const
{
    Q_D(const Storage);
    return d->entityTypes.value(id, 0);
}

/*!
  Returns the EntityType with the ID \a id.
  */
Context *Storage::context(int id) const
{
    Q_D(const Storage);
    return d->contexts.value(id, 0);
}

Context *Storage::context(const QString name) const
{
    Q_D(const Storage);
    return d->contexts.value(d->contextIds.value(name));
}

/*!
  Returns a list of all contexts in this storage.
  */
QList<Context *> Storage::contexts() const
{
    Q_D(const Storage);
    QList<Context *> contexts = d->contexts.values();
    qSort(contexts.begin(), contexts.end(), sortContextByName);
    return contexts;
}

/*!
  Creates a new context in the storage with the name \a name. It will
  automatically create a base entity type for the context named \a
  baseEntityTypeName, since each context has to have exactly one base entity
  type.
  */
Context *Storage::addContext(const QString &name, const QString &baseEntityTypeName)
{
    Q_D(Storage);
    return d->addContext(name, baseEntityTypeName);
}

/*!
  Returns the Attribute with the ID \a id.
  */
Attribute *Storage::attribute(int id) const
{
    Q_D(const Storage);
    return d->attributes.value(id, 0);
}

/*!
  \internal

  Inserts the entity type \a type into the storage-global list of types.
  */
void Storage::insertEntityType(EntityType *type)
{
    Q_D(Storage);
    if(d->entityTypes.contains(type->id()))
        return;

    d->entityTypes.insert(type->id(), type);
}

/*!
  \internal

  Inserts the attribute \a attribute into the storage-global list of attributes.
  */
void Storage::insertAttribute(Attribute *attribute)
{
    Q_D(Storage);
    if(d->attributes.contains(attribute->id()))
        return;

    d->attributes.insert(attribute->id(), attribute);
    d->properties.append(attribute);
}

/*!
  \internal

  Inserts the relation \a relation into the storage-global list of relations.
  */
void Storage::insertRelation(Relation *relation)
{
    Q_D(Storage);
    if(d->relations.contains(relation->id()))
        return;

    d->relations.insert(relation->id(), relation);
    d->properties.append(relation);
}

/*!
  \internal

  Inserts the function \a function into the storage-global list of functions.
  */
void Storage::insertFunction(Function *function)
{
    Q_D(Storage);
    if(d->functions.contains(function->id()))
        return;

    d->functions.insert(function->id(), function);
    d->properties.append(function);
}

QList<Relation *> Storage::relations() const
{
    Q_D(const Storage);
    return d->relations.values();
}

/*!
  Returns the table, which defines all contexts.
  */
Table *Storage::contextsTable() const
{
    Q_D(const Storage);
    return d->contextsTable;
}

/*!
  Returns the table, which defines all entity types.
  */
Table *Storage::entityTypesTable() const
{
    Q_D(const Storage);
    return d->entityTypesTable;
}

/*!
  Returns the table, which defines all attributes.
  */
Table *Storage::attributesTable() const
{
    Q_D(const Storage);
    return d->attributesTable;
}

void Storage::registerContextType(const QString &contextName, QMetaObject metaObject)
{
    Q_D(Storage);
    if(d->contextMetaObjects.contains(contextName))
        return;

    d->contextMetaObjects.insert(contextName, metaObject);
}

/*!
  Opens the storage.
  Returns true upon success and false if something goes wrong (e.g. the file is
  no correct storage).
  */
bool Storage::open()
{
    Q_D(Storage);
    return d->open();
}

/*!
  Returns a list of all entity types, that this storage may contain.
  */
QList<EntityType *> Storage::entityTypes() const
{
    Q_D(const Storage);
    return d->entityTypes.values();
}

} // namespace LBDatabase
