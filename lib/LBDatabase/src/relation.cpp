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
const QString Relation::IdentifierColumn("identifier");
const QString Relation::IdentifierRightColumn("identifierRight");
const QString Relation::DisplayNameLeftColumn("displayName");
const QString Relation::DisplayNameRightColumn("displayNameRight");
const QString Relation::EntityTypeLeftColumn("entitytypeleft");
const QString Relation::EntityTypeRightColumn("entitytyperight");
const QString Relation::CardinalityColumn("cardinality");
const QString Relation::TableNameColumn("tableName");
const QString Relation::ColumnNameColumn("columnName");
const QString Relation::ColumnNameRightColumn("columnNameRight");
const QString Relation::EditableColumn("editable");
const QString Relation::DirectionColumn("direction");

class RelationPrivate {
protected:
    RelationPrivate() :transposeRelation(0)
    {}

    virtual void init();
    void addPropertyValueToEntities();
    void initializeManyToManyRelation();
    void initializeOneToXRelation();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    Row *row;
    Storage *storage;

    QString identifier;
    QString tableName;
    QString columnName;
    QString displayName;
    EntityType *entityType;
    EntityType *entityTypeOther;
    Relation::Cardinality cardinality;
    Relation::Direction direction;
    bool editable;
    bool transpose;

    Table *relationTable;

    TransposeRelation *transposeRelation;

    Relation * q_ptr;
    Q_DECLARE_PUBLIC(Relation)
};

class TransposeRelationPrivate : public RelationPrivate
{
    TransposeRelationPrivate() {}
    void init();

    Q_DECLARE_PUBLIC(TransposeRelation)
};

void RelationPrivate::init()
{
    Q_Q(Relation);

    identifier = row->data(Relation::IdentifierColumn).toString();
    tableName = row->data(Relation::TableNameColumn).toString();
    columnName = row->data(Relation::ColumnNameColumn).toString();
    displayName = row->data(Relation::DisplayNameLeftColumn).toString();
    entityType = storage->entityType(row->data(Relation::EntityTypeLeftColumn).toInt());
    entityTypeOther = storage->entityType(row->data(Relation::EntityTypeRightColumn).toInt());
    cardinality = static_cast<Relation::Cardinality>(row->data(Relation::CardinalityColumn).toInt());
    editable = row->data(Relation::EditableColumn).toBool();
    direction = static_cast<Relation::Direction>(row->data(Relation::DirectionColumn).toInt());
    transpose = false;

    relationTable = storage->database()->table(tableName);

    if(!relationTable)
        qWarning() << "No such table" << tableName << "for relation" << identifier << row->id();

    if(direction == Relation::Both)
        transposeRelation = new TransposeRelation(q);

    entityType->addRelation(q);
    entityType->context()->addRelation(q);
}

void RelationPrivate::addPropertyValueToEntities()
{
    Q_Q(Relation);
    foreach(Entity *entity, entityType->entities()) {
        entity->addRelationValue(new RelationValue<Entity>(q, entity));
    }

    if(transposeRelation)
        transposeRelation->addPropertyValueToEntities();
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
    Column *c1 = relationTable->column(columnName);
    if(!c1) {
        qWarning() << "No such column" << columnName << "for relation" << identifier << row->id();
    }

    Column *c2 = relationTable->column(static_cast<TransposeRelationPrivate *>(transposeRelation->d_func())->columnName);
    if(!c2) {
        qWarning() << "No such column" << static_cast<TransposeRelationPrivate *>(transposeRelation->d_func())->columnName << "for relation" << identifier << row->id();
    }

    int entityTypeLeftColumn = c1->index();
    int entityTypeRightColumn = c2->index();

    foreach(Row *row, relationTable->rows()) {
        int leftId = row->data(entityTypeLeftColumn).toInt();
        int rightId = row->data(entityTypeRightColumn).toInt();
        if(leftId > 0 && rightId > 0) {
            Entity *leftEntity = entityType->context()->entity(leftId);
            Entity *rightEntity = entityTypeOther->context()->entity(rightId);
            if(!leftEntity  || !rightEntity) {
                continue;
            }

            RelationValueBase *leftValue = static_cast<RelationValueBase *>(leftEntity->propertyValue(q));
            RelationValueBase *rightValue = static_cast<RelationValueBase *>(rightEntity->propertyValue(transposeRelation));
            leftValue->addOtherEntity(rightEntity);
            rightValue->addOtherEntity(leftEntity);
        }
    }
}

void RelationPrivate::initializeOneToXRelation()
{
    Q_Q(Relation);

    Column *column = relationTable->column(columnName);
    if(!column) {
        qWarning() << "No such column" << columnName << "for relation" << identifier << row->id();
    }

    int rightColumnIndex = relationTable->column(columnName)->index();

    int leftId;
    Entity *leftEntity;
    RelationValueBase *leftValue;
    RelationValueBase *rightValue;
    foreach(Entity *rightEntity, entityTypeOther->entities()) {
        leftId = rightEntity->row()->data(rightColumnIndex).toInt();
        leftEntity = entityType->context()->entity(leftId);

        if(leftEntity) {
            leftValue = static_cast<RelationValueBase *>(leftEntity->propertyValue(q));
            leftValue->addOtherEntity(rightEntity);

            if(transposeRelation) {
                rightValue = static_cast<RelationValueBase *>(rightEntity->propertyValue(transposeRelation));
                rightValue->addOtherEntity(leftEntity);
            }
        }
    }
}

void RelationPrivate::addPropertyValue(Entity *entity)
{
    Q_Q(Relation);
    entity->addRelationValue(new RelationValue<Entity>(q, entity));
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

Relation::Relation(RelationPrivate &dd, Row *row, Storage *parent) :
    Property(parent),
    d_ptr(&dd)
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
QString Relation::identifier() const
{
    Q_D(const Relation);
    return d->identifier;
}

/*!
  Returns the display name in the given \a context, if its the left or right
  context or name(), if the context has nothing to do with the relation.
  */
QString Relation::displayName() const
{
    Q_D(const Relation);
    return d->displayName;
}

Property::Type Relation::propertyType() const
{
    return Property::Relation;
}

/*!
  Sets the display name in the given \a context.

  Does nothing if the context has nothing to do with the context.
  */
void Relation::setDisplayName(const QString &displayName)
{
    Q_D(Relation);
    d->row->setData(DisplayNameLeftColumn, QVariant(displayName));
    emit displayNameChanged(displayName);
}

/*!
  Returns the entity type from which the relation maps.
  */
EntityType *Relation::entityType() const
{
    Q_D(const Relation);
    return d->entityType;
}

EntityType *Relation::entityTypeOther() const
{
    Q_D(const Relation);
    return d->entityTypeOther;
}

/*!
  Returns the cardinality of the relation.
  */
Relation::Cardinality Relation::cardinality() const
{
    Q_D(const Relation);
    return d->cardinality;
}

Relation::Direction Relation::direction() const
{
    Q_D(const Relation);
    return d->direction;
}

bool Relation::isEditable() const
{
    Q_D(const Relation);
    return d->editable;
}

bool Relation::isTranspose() const
{
    Q_D(const Relation);
    return d->transpose;
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

Storage* Relation::storage() const
{
    Q_D(const Relation);
    return d->storage;
}

Row *Relation::row() const
{
    Q_D(const Relation);
    return d->row;
}

TransposeRelation::TransposeRelation(Relation *relation) :
    Relation(*new TransposeRelationPrivate, relation->row(), relation->storage())
{
}

TransposeRelation::~TransposeRelation()
{
}

void TransposeRelationPrivate::init()
{
    Q_Q(Relation);

    identifier = row->data(Relation::IdentifierRightColumn).toString();
    tableName = row->data(Relation::TableNameColumn).toString();
    columnName = row->data(Relation::ColumnNameRightColumn).toString();
    displayName = row->data(Relation::DisplayNameRightColumn).toString();
    entityType = storage->entityType(row->data(Relation::EntityTypeRightColumn).toInt());
    entityTypeOther = storage->entityType(row->data(Relation::EntityTypeLeftColumn).toInt());
    cardinality = static_cast<Relation::Cardinality>(row->data(Relation::CardinalityColumn).toInt());
    editable = row->data(Relation::EditableColumn).toBool();
    direction = static_cast<Relation::Direction>(row->data(Relation::DirectionColumn).toInt());
    transpose = true;

    relationTable = storage->database()->table(tableName);

    entityType->addRelation(q);
    entityType->context()->addRelation(q);
}

} // namespace LBDatabase
