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
const QString Function::NameColumn("name");
const QString Function::DisplayNameColumn("displayName");
const QString Function::EntityTypeColumn("entityType");
const QString Function::KeyEntityTypeRightColumn("keyEntityType");
const QString Function::CalculatedColumn("calculated");
const QString Function::CacheDataColumn("cacheData");
const QString Function::TypeColumn("type");

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

    Row *row;
    Storage *storage;
    EntityType *entityType;
    EntityType *keyEntityType;
    Attribute::Type type;

    bool calculated;
    bool cacheData;
    QString name;
    QString displayName;

    Table *functionTable;

    QList<EntityType *> reimplementingEntityTypes;

    Function * q_ptr;
    Q_DECLARE_PUBLIC(Function)
};

void FunctionPrivate::init()
{
    Q_Q(Function);
    name = row->data(Function::NameColumn).toString();
    displayName = row->data(Function::DisplayNameColumn).toString();
    entityType = storage->entityType(row->data(Function::EntityTypeColumn).toInt());
    keyEntityType = storage->entityType(row->data(Function::KeyEntityTypeRightColumn).toInt());
    calculated = row->data(Function::CalculatedColumn).toBool();
    cacheData = row->data(Function::CacheDataColumn).toBool();
    type = static_cast<Attribute::Type>(row->data(Function::TypeColumn).toInt());

    if(!calculated) {
        functionTable = storage->database()->table(name);

        if(!functionTable) {
            qWarning() << "No such table:" << name << "for function" << row->id();
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
        int entityColumn = functionTable->column(entityType->identifier())->index();
        int keyEntityColumn = functionTable->column(keyEntityType->identifier())->index();
        int valueColumn = functionTable->column(name)->index();
        Entity *entity;
        Entity *keyEntity;
        QVariant value;
        FunctionValue *functionValue;
        foreach(Row *row, functionTable->rows()) {
            entity = entityType->context()->entity(row->data(entityColumn).toInt());
            keyEntity = keyEntityType->context()->entity(row->data(keyEntityColumn).toInt());
            value = row->data(valueColumn);

            functionValue = static_cast<FunctionValue *>(entity->propertyValue(q));
            functionValue->addValue(keyEntity, value);
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

QString Function::displayName(const Context *context) const
{
    Q_D(const Function);
    Q_UNUSED(context);
    return d->displayName;
}

void Function::setDisplayName(const QString &displayName, const Context *context)
{
    Q_D(Function);
    Q_UNUSED(context);
    if(d->displayName == displayName)
        return;

    d->row->setData(Attribute::DisplayNameColumn, QVariant(displayName));
    d->displayName = displayName;
    emit displayNameChanged(displayName, d->entityType->context());
}

QString Function::name() const
{
    Q_D(const Function);
    return d->name;
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
