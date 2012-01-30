#ifndef LBDATABASE_ATTRIBUTEVALUE_H
#define LBDATABASE_ATTRIBUTEVALUE_H

#include "propertyvalue.h"

namespace LBDatabase {

class Attribute;
class Entity;

class AttributeValuePrivate;
class AttributeValue : public PropertyValue
{
    Q_OBJECT
public:
    ~AttributeValue();

    Entity *entity() const;
    Property *property() const;
    QVariant data(int role = Qt::DisplayRole) const;
    bool setData(const QVariant &data);

    bool isEditable() const;

private:
    friend class AttributePrivate;

    explicit AttributeValue(Attribute *attribute, Entity *parent);

    void fetchValue();
    void calculate();

    QScopedPointer<AttributeValuePrivate> d_ptr;
    Q_DECLARE_PRIVATE(AttributeValue)
    Q_DISABLE_COPY(AttributeValue)
};

} // namespace LBDatabase

#endif // LBDATABASE_ATTRIBUTEVALUE_H
