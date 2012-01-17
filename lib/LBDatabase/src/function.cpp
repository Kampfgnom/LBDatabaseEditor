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

namespace LBDatabase {

/******************************************************************************
** FunctionPrivate
*/
const QString Function::NameColumn("name");
const QString Function::DisplayNameColumn("displayName");
const QString Function::EntityTypeColumn("entityType");
const QString Function::KeyEntityTypeRightColumn("keyEntityType");

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

    QString name;
    QString displayName;

    Table *functionTable;

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

    functionTable = storage->database()->table(name);

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
    int entityColumn = functionTable->column(entityType->name())->index();
    int keyEntityColumn = functionTable->column(keyEntityType->name())->index();
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
