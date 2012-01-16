#ifndef LBDATABASE_ENTITY_H
#define LBDATABASE_ENTITY_H

#include <QObject>

#include <QHash>

namespace LBDatabase {

class Attribute;
class AttributeValue;
class Context;
class EntityType;
class FunctionValue;
class Property;
class PropertyValue;
class Relation;
class RelationValue;
class Row;
class Storage;

class EntityPrivate;
class Entity : public QObject
{
    Q_OBJECT
public:
    //! \cond PRIVATE
    static const QString EntityTypeIdColumn;
    //! \endcond

    ~Entity();

    virtual QString displayName(int role = Qt::DisplayRole) const;

    EntityType *entityType() const;
    Storage *storage() const;
    Context *context() const;
    QList<PropertyValue *> propertyValues() const;
    PropertyValue *propertyValue(Property *property) const;

    Row *row() const;

private:
    friend class AttributePrivate;
    friend class ContextPrivate;
    friend class RelationPrivate;
    friend class Context;
    friend class FunctionPrivate;

    explicit Entity(Row *row, Context *parent);

    QVariant data(Property *property) const;
    bool setData(const QVariant &data, Property *property);

    void addAttributeValue(AttributeValue *value);
    void addRelationValue(RelationValue *value);
    void addFunctionValue(FunctionValue *value);

    QScopedPointer<EntityPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Entity)
    Q_DISABLE_COPY(Entity)
};

} // namespace LBDatabase

#endif // LBDATABASE_ENTITY_H
