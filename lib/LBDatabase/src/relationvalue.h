#ifndef LBDATABASE_RELATIONVALUE_H
#define LBDATABASE_RELATIONVALUE_H

#include "propertyvalue.h"

#include "functionvalue.h"

namespace LBDatabase {

class Relation;
class Entity;

class RelationValuePrivate;
class RelationValue : public PropertyValue
{
    Q_OBJECT
public:
    ~RelationValue();

    virtual Entity *entity() const;
    Property *property() const;

    Entity *firstEntity() const;
    QList<Entity *> entities() const;

    bool isEditable() const;
    virtual bool setData(const QVariant &data);
    QVariant data(int role = Qt::DisplayRole) const;

    template<class EntityType>
    QList<EntityType *> cast()
    {
        QList<EntityType *> list;
        foreach(Entity *entity, entities())
            list.append(static_cast<EntityType *>(entity));

        return list;
    }

    template<typename SortType, class EntityType>
    QList<EntityType *> sort(FunctionValue *sortFunction)
    {
        QMap<SortType, EntityType *> map;
        foreach(Entity *entity, entities())
            map.insert(sortFunction->value(entity).value<SortType>(), static_cast<EntityType *>(entity));

        return map.values();
    }

protected:
    friend class RelationPrivate;

    explicit RelationValue(Relation *relation, Entity *parent);

    void fetchValue();
    void calculate();
    void addOtherEntity(Entity *entity);

    QScopedPointer<RelationValuePrivate> d_ptr;
    Q_DECLARE_PRIVATE(RelationValue)
    Q_DISABLE_COPY(RelationValue)
};

} // namespace LBDatabase

Q_DECLARE_METATYPE(QList<LBDatabase::Entity *>)

#endif // LBDATABASE_RELATIONVALUE_H
