#ifndef LBDATABASE_FUNCTIONVALUE_H
#define LBDATABASE_FUNCTIONVALUE_H

#include "propertyvalue.h"

namespace LBDatabase {

class Function;
class Row;

class FunctionValuePrivate;
class FunctionValue : public PropertyValue
{
    Q_OBJECT
public:
    ~FunctionValue();

    Entity *entity() const;
    Property *property() const;
    QVariant value(const Entity *entity) const;
    QVariant data(int role = Qt::DisplayRole) const;
    bool setData(const QVariant &data);

    void setValue(Entity *key, const QVariant &value);

    bool isEditable() const;

Q_SIGNALS:
    void valueChanged(Entity *key, QVariant value);

private:
    friend class FunctionPrivate;

    explicit FunctionValue(Function *function, Entity *parent);

    void fetchValue();
    void calculate();

    void addValue(Entity *key, const QVariant &value, Row *row);

    QScopedPointer<FunctionValuePrivate> d_ptr;
    Q_DECLARE_PRIVATE(FunctionValue)
    Q_DISABLE_COPY(FunctionValue)
};

} // namespace LBDatabase

#endif // LBDATABASE_FUNCTIONVALUE_H
