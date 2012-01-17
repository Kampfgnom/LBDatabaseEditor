#include "relationvalue.h"
#include "relationvalue_p.h"

#include "context.h"
#include "entity.h"
#include "entitytype.h"
#include "relation.h"
#include "row.h"

namespace LBDatabase {

/******************************************************************************
** RelationValuePrivate
*/

//! \cond PRIVATE
void RelationValuePrivate::init()
{
    Q_Q(RelationValue);
    QObject::connect(q, SIGNAL(dataChanged(QVariant)), entity->context(), SLOT(onPropertyValueDataChanged(QVariant)));
}

void RelationValuePrivate::fetchValue()
{
}

void RelationValuePrivate::addOtherEntity(Entity *entity)
{
    if(!otherEntities.contains(entity))
        otherEntities.append(entity);
}
//! \endcond

/******************************************************************************
** RelationValue
*/
/*!
  \class RelationValue
  \brief The RelationValue class represents a value of a relation between two
  EntityTypes.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var RelationValue::d_ptr
  \internal
  */

/*!
  Creates a RelationValue.
  */
RelationValue::RelationValue(Relation *relation, Entity *parent) :
    PropertyValue(parent),
    d_ptr(new RelationValuePrivate)
{
    Q_D(RelationValue);
    d->q_ptr = this;
    d->relation = relation;
    d->entity = parent;
    d->init();
}

/*!
  Destroys the relation value.
  */
RelationValue::~RelationValue()
{
}

/*!
  Returns the entity of this relation value.
  */
Entity *RelationValue::entity() const
{
    Q_D(const RelationValue);
    return d->entity;
}

/*!
  Returns the entities to which this relation maps.
  */
QList<Entity *> RelationValue::entities() const
{
    Q_D(const RelationValue);
    return d->otherEntities;
}

/*!
  Does nothing.
  */
bool RelationValue::setData(const QVariant &data)
{
    Q_UNUSED(data);
    return false;
}

/*!
  Returns a QVariant, which represents the content of the relation in the given role.

  Currently this method supports only the Qt::DisplayRole.
  */
QVariant RelationValue::data(int role) const
{
    Q_D(const RelationValue);
    if(role == Qt::DisplayRole) {
        if(d->otherEntities.isEmpty())
            return QVariant();

        if(d->otherEntities.size() == 1)
            return d->otherEntities.at(0)->displayName();

        return QVariant(QString::number(d->otherEntities.size())+QLatin1String(" ")+d->otherEntities.at(0)->entityType()->name()+QLatin1String("s"));
    }
    else if(role == PropertyValue::PlainDataRole) {
        return QVariant::fromValue<QList<Entity *> >(d->otherEntities);
    }

    return QVariant();
}

/*!
  Returns false
  */
bool RelationValue::isEditable() const
{
    return false;
}

/*!
  Returns the relation, that describes this value.
  */
Property *RelationValue::property() const
{
    Q_D(const RelationValue);
    return d->relation;
}

Entity *RelationValue::firstEntity() const
{
    Q_D(const RelationValue);
    if(d->otherEntities.isEmpty())
        return 0;

    return d->otherEntities.first();
}

/*!
  Initializes the content of the relation value.
  */
void RelationValue::fetchValue()
{
    Q_D(RelationValue);
    d->fetchValue();
}

void RelationValue::calculate()
{
}

void RelationValue::addOtherEntity(Entity *entity)
{
    Q_D(RelationValue);
    d->addOtherEntity(entity);
}

} // namespace LBDatabase
