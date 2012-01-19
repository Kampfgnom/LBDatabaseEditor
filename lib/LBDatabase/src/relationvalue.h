#ifndef LBDATABASE_RELATIONVALUE_H
#define LBDATABASE_RELATIONVALUE_H

#include "propertyvalue.h"

#include "functionvalue.h"

#include <QVariant>

namespace LBDatabase {

class Relation;
class Entity;

class RelationValueBasePrivate;
class RelationValueBase : public PropertyValue
{
    Q_OBJECT
public:
    ~RelationValueBase();

    virtual Entity *entity() const;
    Property *property() const;

    Entity *firstEntity() const;

    bool isEditable() const;
    virtual bool setData(const QVariant &data);
    QVariant data(int role = Qt::DisplayRole) const = 0;


protected:
    friend class RelationPrivate;

    explicit RelationValueBase(Relation *relation, Entity *parent);

    void fetchValue();
    void calculate();
    virtual void addOtherEntity(Entity *entity) = 0;

    QScopedPointer<RelationValueBasePrivate> d_ptr;
    Q_DECLARE_PRIVATE(RelationValueBase)
    Q_DISABLE_COPY(RelationValueBase)
};

template<class EntityClass, class SortType>
class FunctionSorter;

enum SortingDirection {
    SortAscending,
    SortDescending
};

template<class EntityClass>
class RelationValue : public RelationValueBase
{
public:
    template<typename SortType>
    QList<EntityClass *> sort(FunctionValue *sortFunction, SortingDirection dir = SortAscending)
    {
        if(otherEntities.contains(sortFunction))
            return otherEntities.value(sortFunction);


        QList<EntityClass *> list = otherEntities.value(0);

        qSort(list.begin(), list.end(), FunctionSorter<EntityClass, SortType>(sortFunction, dir));

        otherEntities.insert(sortFunction, list);
        return list;
    }

    /*!
      Returns a QVariant, which represents the content of the relation in the given role.

      Currently this method supports only the Qt::DisplayRole.
      */
    QVariant data(int role) const
    {
        if(role == Qt::DisplayRole) {
            if(otherEntities.value(0).isEmpty())
                return QVariant();

            if(otherEntities.value(0).size() == 1)
                return otherEntities.value(0).at(0)->displayName();

            return QVariant(QString::number(entities().size())+QLatin1String(" ")+otherEntities.value(0).at(0)->entityType()->name()+QLatin1String("s"));
        }
        else if(role == PropertyValue::PlainDataRole) {
            return QVariant::fromValue<QList<Entity *> >(otherEntities.value(0));
        }

        return QVariant();
    }

    RelationValue(Relation *relation, Entity *parent) :
        RelationValueBase(relation, parent)
    {
    }

    QList<EntityClass *> entities() const
    {
        return otherEntities.value(0);
    }

    EntityClass *firstEntity() const
    {
        if(otherEntities.value(0).isEmpty())
            return 0;

        return otherEntities.value(0).first();
    }

private:
    void addOtherEntity(Entity *entity)
    {
        QList<EntityClass *> entities = otherEntities.value(0);
        EntityClass *entityCasted = static_cast<EntityClass *>(entity);
        if(!entities.contains(entityCasted)) {
            entities.append(entityCasted);
            otherEntities.insert(0, entities);
        }
    }

    QHash<FunctionValue *, QList<EntityClass *> > otherEntities;
};

template<class EntityClass, class SortType>
class FunctionSorter
{
public:

    FunctionSorter(FunctionValue *value, SortingDirection dir) : m_value(value), m_dir(dir) {}

    bool operator()(const EntityClass *left, const EntityClass *right) const
    {
        QVariant leftVariant = m_value->value(left);
        SortType leftValue = leftVariant.value<SortType>();
        QVariant rightVariant = m_value->value(right);
        SortType rightValue = rightVariant.value<SortType>();
        if(m_dir == SortAscending) {
            return rightValue > leftValue;
        }
        else {
            return rightValue < leftValue;
        }
    }

    FunctionValue *m_value;
    SortingDirection m_dir;
};

} // namespace LBDatabase

Q_DECLARE_METATYPE(QList<LBDatabase::Entity *>)

#endif // LBDATABASE_RELATIONVALUE_H
