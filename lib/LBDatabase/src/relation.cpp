#include "relation.h"

#include "attribute.h"
#include "column.h"
#include "context.h"
#include "database.h"
#include "entity.h"
#include "entitytype.h"
#include "relationvalue.h"
#include "relationvalue_p.h"
#include "row.h"
#include "storage.h"
#include "table.h"

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** RelationPrivate
*/
//! \cond PRIVATE
const QString Relation::NameColumn("name");
const QString Relation::DisplayNameLeftColumn("displaynameleft");
const QString Relation::DisplayNameRightColumn("displaynameright");
const QString Relation::EntityTypeLeftColumn("entitytypeleft");
const QString Relation::EntityTypeRightColumn("entitytyperight");
const QString Relation::CardinalityColumn("cardinality");
const QString Relation::ColumnOrTableNameColumn("columnOrTableName");

class RelationPrivate {
    RelationPrivate() :
        entityTypeLeft(0), entityTypeRight(0),
        cardinality(Relation::OneToOne),
        relationTable(0)
    {}

    void init();
    void addPropertyValueToEntities();
    void initializeManyToManyRelation();
    void initializeOneToXRelation();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    Row *row;
    Storage *storage;

    QString name;
    QString columnOrTableName;
    QString displayNameLeft;
    QString displayNameRight;
    EntityType *entityTypeLeft;
    EntityType *entityTypeRight;
    Relation::Cardinality cardinality;

    Table *relationTable;

    Relation * q_ptr;
    Q_DECLARE_PUBLIC(Relation)
};

void RelationPrivate::init()
{
    Q_Q(Relation);

    name = row->data(Relation::NameColumn).toString();
    columnOrTableName = row->data(Relation::ColumnOrTableNameColumn).toString();
    displayNameLeft = row->data(Relation::DisplayNameLeftColumn).toString();
    displayNameRight = row->data(Relation::DisplayNameRightColumn).toString();
    entityTypeLeft = storage->entityType(row->data(Relation::EntityTypeLeftColumn).toInt());
    entityTypeRight = storage->entityType(row->data(Relation::EntityTypeRightColumn).toInt());
    cardinality = static_cast<Relation::Cardinality>(row->data(Relation::CardinalityColumn).toInt());

    relationTable = storage->database()->table(columnOrTableName);

    if(entityTypeLeft) {
        entityTypeLeft->addRelation(q);
        entityTypeLeft->context()->addRelation(q);
    }
    if(entityTypeRight) {
        entityTypeRight->addRelation(q);
        entityTypeRight->context()->addRelation(q);
    }
}

void RelationPrivate::addPropertyValueToEntities()
{
    Q_Q(Relation);
    foreach(Entity *entity, entityTypeLeft->entities()) {
        entity->addRelationValue(q->createLeftValue(entity));
    }
    foreach(Entity *entity, entityTypeRight->entities()) {
        entity->addRelationValue(q->createRightValue(entity));
    }
}

void RelationPrivate::fetchValues()
{
    switch(cardinality) {
    case Relation::OneToOne:
    case Relation::OneToMany:
        initializeOneToXRelation();
        break;
    case Relation::ManyToMany:
        initializeManyToManyRelation();
        break;
    }
}

void RelationPrivate::initializeManyToManyRelation()
{
    Q_Q(Relation);
    Column *c1 = relationTable->column(entityTypeLeft->name());
    int entityTypeLeftColumn = -1;
    if(c1)
        entityTypeLeftColumn = c1->index();

    Column *c2 = relationTable->column(entityTypeRight->name());
    int entityTypeRightColumn = -1;
    if(c2)
        entityTypeRightColumn = c2->index();

    if(entityTypeLeftColumn >= 0 && entityTypeRightColumn >= 0) {
    foreach(Row *row, relationTable->rows()) {
            int leftId = row->data(entityTypeLeftColumn).toInt();
            int rightId = row->data(entityTypeRightColumn).toInt();
            if(leftId > 0 && rightId > 0) {
                Entity *leftEntity = entityTypeLeft->context()->entity(leftId);
                Entity *rightEntity = entityTypeRight->context()->entity(rightId);
                RelationValueBase *leftValue = static_cast<RelationValueBase *>(leftEntity->propertyValue(q));
                RelationValueBase *rightValue = static_cast<RelationValueBase *>(rightEntity->propertyValue(q));
                leftValue->addOtherEntity(rightEntity);
                rightValue->addOtherEntity(leftEntity);
            }
        }
    }
}

void RelationPrivate::initializeOneToXRelation()
{
    Q_Q(Relation);

    int rightColumnIndex = entityTypeRight->context()->table()->column(columnOrTableName)->index();

    int leftId;
    Entity *leftEntity;
    RelationValueBase *leftValue;
    RelationValueBase *rightValue;
    foreach(Entity *rightEntity, entityTypeRight->entities()) {
        leftId = rightEntity->row()->data(rightColumnIndex).toInt();
        leftEntity = entityTypeLeft->context()->entity(leftId);

        if(leftEntity) {
            leftValue = static_cast<RelationValueBase *>(leftEntity->propertyValue(q));
            rightValue = static_cast<RelationValueBase *>(rightEntity->propertyValue(q));
            leftValue->addOtherEntity(rightEntity);
            rightValue->addOtherEntity(leftEntity);
        }
    }
}

void RelationPrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Relation);
    if(entity->entityType() == entityTypeLeft) {
        entity->addRelationValue(q->createLeftValue(entity));
    }
    else {
        entity->addRelationValue(q->createRightValue(entity));
    }
}

//! \endcond

/******************************************************************************
** Relation
*/
/*!
  \class Relation
  \brief The Relation class represents a description of a relation between two
  EntityTypes.

  \ingroup highlevel-database-classes

  \todo Dokument
  */

/*!
  \var Relation::d_ptr
  \internal
  */

/*!
  \enum Relation::Cardinality

  This enumeration describes the cardinality of a relation.

  */

/*!
  Creates a relation in the given \a storage, which is described by \a row.
  */
Relation::Relation(Row *row, Storage *parent) :
    Property(parent),
    d_ptr(new RelationPrivate)
{
    Q_D(Relation);
    d->q_ptr = this;
    d->row = row;
    d->storage = parent;
    d->init();
}

/*!
  Destroys the relation.
  */
Relation::~Relation()
{
}

/*!
  Returns the storage-global ID of the relation.
  */
int Relation::id() const
{
    Q_D(const Relation);
    return d->row->id();
}

/*!
  Returns the name of the relation. If the relation has a 1:N cardinality this
  is the name of the column in the left context, if the cardinatlity is N:M, it
  is the name of the table, which stores the pairs of the relation.
  */
QString Relation::name() const
{
    Q_D(const Relation);
    return d->name;
}

/*!
  Returns the display name in the given \a context, if its the left or right
  context or name(), if the context has nothing to do with the relation.
  */
QString Relation::displayName(const Context *context) const
{
    Q_D(const Relation);
    if(context) {
        if(d->entityTypeLeft && context == d->entityTypeLeft->context())
            return d->displayNameLeft;
        else if(d->entityTypeRight && context == d->entityTypeRight->context())
            return d->displayNameRight;
    }

    return d->name;
}

QString Relation::displayNameLeft() const
{
    Q_D(const Relation);
    return d->displayNameLeft;
}

QString Relation::displayNameRight() const
{
    Q_D(const Relation);
    return d->displayNameRight;
}

/*!
  Sets the display name in the given \a context.

  Does nothing if the context has nothing to do with the context.
  */
void Relation::setDisplayName(const QString &displayName, const Context *context)
{
    Q_D(Relation);
    if(context) {
        if(d->entityTypeLeft && context == d->entityTypeLeft->context()) {
            d->row->setData(DisplayNameLeftColumn, QVariant(displayName));
            emit displayNameChanged(displayName, d->entityTypeLeft->context());
        }
        else if(d->entityTypeRight && context == d->entityTypeRight->context()) {
            d->row->setData(DisplayNameRightColumn, QVariant(displayName));
            emit displayNameChanged(displayName, d->entityTypeRight->context());
        }
    }
}

/*!
  Returns the entity type from which the relation maps.
  */
EntityType *Relation::entityTypeLeft() const
{
    Q_D(const Relation);
    return d->entityTypeLeft;
}

/*!
  Returns the entity type to which the relation maps.
  */
EntityType *Relation::entityTypeRight() const
{
    Q_D(const Relation);
    return d->entityTypeRight;
}

/*!
  Returns the cardinality of the relation.
  */
Relation::Cardinality Relation::cardinality() const
{
    Q_D(const Relation);
    return d->cardinality;
}

/*!
  \internal

  Adds a RelationValueLeft to each Entity of the left EntityType and a
  RelationValueRight to each Entity of the right one.
  */
void Relation::addPropertyValueToEntities()
{
    Q_D(Relation);
    return d->addPropertyValueToEntities();
}

/*!
  \internal

  Adds a RelationValueLeft or Right to \a entity, if its of the leftEntityType()
  respectively rightEntityType().

  Does nothing if \a entity is of unkown type.
  */
void Relation::addPropertyValue(Entity *entity)
{
    Q_D(Relation);
    return d->addPropertyValue(entity);
}

void Relation::fetchValues()
{
    Q_D(Relation);
    return d->fetchValues();
}

RelationValueBase *Relation::createLeftValue(Entity *entity)
{
    return new RelationValue<Entity>(this, entity);
}

RelationValueBase *Relation::createRightValue(Entity *entity)
{
    return new RelationValue<Entity>(this, entity);
}

Storage* Relation::storage() const
{
    Q_D(const Relation);
    return d->storage;
}

} // namespace LBDatabase
