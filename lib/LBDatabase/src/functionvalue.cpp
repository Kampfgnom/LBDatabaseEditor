#include "functionvalue.h"

#include "context.h"
#include "entity.h"
#include "function.h"

namespace LBDatabase {

/******************************************************************************
** FunctionValuePrivate
*/
class FunctionValuePrivate {
    FunctionValuePrivate() {}

    void init();
    void fetchValue();

    Entity *entity;
    Function *function;

    QHash<Entity *, QVariant> values;

    FunctionValue * q_ptr;
    Q_DECLARE_PUBLIC(FunctionValue)
};

void FunctionValuePrivate::init()
{
    Q_Q(FunctionValue);
    QObject::connect(q, SIGNAL(dataChanged(QVariant)), entity->context(), SLOT(onPropertyValueDataChanged(QVariant)));
}

void FunctionValuePrivate::fetchValue()
{
}

/******************************************************************************
** FunctionValue
*/
FunctionValue::FunctionValue(Function *function, Entity *parent) :
    PropertyValue(parent),
    d_ptr(new FunctionValuePrivate)
{
    Q_D(FunctionValue);
    d->q_ptr = this;
    d->function = function;
    d->entity = parent;
    d->init();
}

void FunctionValue::fetchValue()
{
    Q_D(FunctionValue);
    d->fetchValue();
}

void FunctionValue::addValue(Entity *key, const QVariant &value)
{
    Q_D(FunctionValue);
    d->values.insert(key, value);
}

FunctionValue::~FunctionValue()
{
}

Entity *FunctionValue::entity() const
{
    Q_D(const FunctionValue);
    return d->entity;
}

Property *FunctionValue::property() const
{
    Q_D(const FunctionValue);
    return d->function;
}

QVariant FunctionValue::data(int role) const
{
    Q_D(const FunctionValue);
    Q_UNUSED(role);

    if(role == Qt::DisplayRole) {
        if(d->values.isEmpty())
            return QVariant();

        if(d->values.size() == 1) {
            Entity *key = d->values.keys().at(0);
            QVariant value = d->values.value(key);
            return QVariant(key->displayName() + QLatin1String("=") + value.toString());
        }

        return QVariant(QString::number(d->values.size()) +QLatin1String(" values"));
    }

    return QVariant();
}

bool FunctionValue::setData(const QVariant &data)
{
    return false;
}

bool FunctionValue::isEditable() const
{
    return false;
}

} // namespace LBDatabase
