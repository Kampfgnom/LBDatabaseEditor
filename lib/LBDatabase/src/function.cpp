#include "function.h"

#include "attribute.h"
#include "column.h"
#include "context.h"
#include "database.h"
#include "entity.h"
#include "entitytype.h"
#include "functionvalue.h"
#include "row.h"
#include "storage.h"
#include "table.h"

#include <QDebug>
#include <QThread>

namespace LBDatabase {

/******************************************************************************
** FunctionPrivate
*/
const QString Function::IdentifierColumn("identifier");
const QString Function::TableNameColumn("tableName");
const QString Function::EntityColumnNameColumn("entityColumnName");
const QString Function::KeyEntityColumnNameColumn("keyEntityColumnName");
const QString Function::ValueColumnNameColumn("valueColumnName");
const QString Function::DisplayNameColumn("displayName");
const QString Function::EntityTypeColumn("entityType");
const QString Function::KeyEntityTypeRightColumn("keyEntityType");
const QString Function::CalculatedColumn("calculated");
const QString Function::CacheDataColumn("cacheData");
const QString Function::TypeColumn("type");
const QString Function::EditableColumn("editable");

const QString Function::FunctionReimplementationsTable("lbmeta_functionreimplementations");
const QString Function::ReimplementedFunctionColumn("function");
const QString Function::ReimplementingEntityTypeColumn("reimplementingEntityType");

class FunctionPrivate {
    FunctionPrivate() :
        entityType(0),
        keyEntityType(0),
        functionTable(0)
    {}

    void init();
    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    void setValue(Entity *key, const QVariant &value);

    Row *row;
    Storage *storage;
    EntityType *entityType;
    EntityType *keyEntityType;
    Attribute::Type type;

    bool calculated;
    bool cacheData;
    bool editable;
    QString identifier;
    QString displayName;
    QString tableName;
    QString entityColumnName;
    QString keyEntityColumnName;
    QString valueColumnName;

    Table *functionTable;

    QList<EntityType *> reimplementingEntityTypes;

    Function * q_ptr;
    Q_DECLARE_PUBLIC(Function)
};

void FunctionPrivate::init()
{
    Q_Q(Function);
    identifier = row->data(Function::IdentifierColumn).toString();
    displayName = row->data(Function::DisplayNameColumn).toString();
    entityType = storage->entityType(row->data(Function::EntityTypeColumn).toInt());
    keyEntityType = storage->entityType(row->data(Function::KeyEntityTypeRightColumn).toInt());
    calculated = row->data(Function::CalculatedColumn).toBool();
    cacheData = row->data(Function::CacheDataColumn).toBool();
    editable = row->data(Function::EditableColumn).toBool();
    type = static_cast<Attribute::Type>(row->data(Function::TypeColumn).toInt());

    tableName = row->data(Function::TableNameColumn).toString();
    entityColumnName = row->data(Function::EntityColumnNameColumn).toString();
    keyEntityColumnName = row->data(Function::KeyEntityColumnNameColumn).toString();
    valueColumnName = row->data(Function::ValueColumnNameColumn).toString();

    if(!calculated) {
        functionTable = storage->database()->table(tableName);

        if(!functionTable) {
            qWarning() << "No such table:" << identifier << "for function" << row->id();
        }
    }

    entityType->addFunction(q);
    entityType->context()->addFunction(q);
}

void FunctionPrivate::addPropertyValueToEntities()
{
    Q_Q(Function);
    foreach(Entity *entity, entityType->entities()) {
        entity->addFunctionValue(new FunctionValue(q, entity));
    }
}

void FunctionPrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Function);
    entity->addFunctionValue(new FunctionValue(q, entity));
}

void FunctionPrivate::fetchValues()
{
    Q_Q(Function);
    if(!calculated) {
        int entityColumn = functionTable->column(entityColumnName)->index();
        int keyEntityColumn = functionTable->column(keyEntityColumnName)->index();
        int valueColumn = functionTable->column(valueColumnName)->index();
        Entity *entity;
        Entity *keyEntity;
        QVariant value;
        FunctionValue *functionValue;
        foreach(Row *row, functionTable->rows()) {
            entity = entityType->context()->entity(row->data(entityColumn).toInt());
            keyEntity = keyEntityType->context()->entity(row->data(keyEntityColumn).toInt());
            value = row->data(valueColumn);
            if(!entity || !keyEntity)
                continue;

            functionValue = static_cast<FunctionValue *>(entity->propertyValue(q));
            functionValue->addValue(keyEntity, value, row);
        }
    }
}

/******************************************************************************
** Function
*/
Function::Function(Row *row, Storage *parent) :
    Property(parent),
    d_ptr(new FunctionPrivate)
{
    Q_D(Function);
    d->q_ptr = this;
    d->row = row;
    d->storage = parent;
    d->init();
}

void Function::addReimplementingEntityType(EntityType *type)
{
    Q_D(Function);
    d->reimplementingEntityTypes.append(type);
}

Function::~Function()
{
}

int Function::id() const
{
    Q_D(const Function);
    return d->row->id();
}

Property::Type Function::propertyType() const
{
    return Property::Function;
}

Table *Function::functionTable() const
{
    Q_D(const Function);
    return d->functionTable;
}

QString Function::entityColumnName() const
{
    Q_D(const Function);
    return d->entityColumnName;
}

QString Function::keyEntityColumnName() const
{
    Q_D(const Function);
    return d->keyEntityColumnName;
}

QString Function::valueColumnName() const
{
    Q_D(const Function);
    return d->valueColumnName;
}

QString Function::displayName() const
{
    Q_D(const Function);
    return d->displayName;
}

void Function::setDisplayName(const QString &displayName)
{
    Q_D(Function);
    if(d->displayName == displayName)
        return;

    d->row->setData(Attribute::DisplayNameColumn, QVariant(displayName));
    d->displayName = displayName;
    emit displayNameChanged(displayName);
}

QString Function::identifier() const
{
    Q_D(const Function);
    return d->identifier;
}

EntityType *Function::keyEntityType() const
{
    Q_D(const Function);
    return d->keyEntityType;
}

QString Function::qtTypeName() const
{
    Q_D(const Function);
    return Attribute::typeToQtType(d->type);
}

bool Function::isCalculated() const
{
    Q_D(const Function);
    return d->calculated;
}

bool Function::cacheData() const
{
    Q_D(const Function);
    return d->cacheData;
}

bool Function::isEditable() const
{
    Q_D(const Function);
    return d->editable;
}

QList<EntityType *> Function::reimplementingEntityTypes() const
{
    Q_D(const Function);
    return d->reimplementingEntityTypes;
}

void Function::addPropertyValueToEntities()
{
    Q_D(Function);
    d->addPropertyValueToEntities();
}

void Function::addPropertyValue(Entity *entity)
{
    Q_D(Function);
    d->addPropertyValue(entity);
}

void Function::fetchValues()
{
    Q_D(Function);
    d->fetchValues();
}

} // namespace LBDatabase
