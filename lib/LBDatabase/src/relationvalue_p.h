#ifndef LBDATABASE_RELATIONVALUE_P_H
#define LBDATABASE_RELATIONVALUE_P_H

#include <QObject>

namespace LBDatabase {

class Entity;
class Relation;
class RelationValue;

//! \cond PRIVATE
class RelationValuePrivate {
protected:
    friend class RelationPrivate;

    RelationValuePrivate() {}

    virtual void init();
    virtual void fetchValue();

    void addOtherEntity(Entity *entity);

    Entity *entity;
    Relation *relation;
    QList<Entity *> otherEntities;

    RelationValue * q_ptr;
    Q_DECLARE_PUBLIC(RelationValue)
};
//! \endcond

} // namespace LBDatabase

#endif // LBDATABASE_RELATIONVALUE_P_H
