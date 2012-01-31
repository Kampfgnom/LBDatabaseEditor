#ifndef LBDATABASE_RELATION_H
#define LBDATABASE_RELATION_H

#include "property.h"

namespace LBDatabase {

class Context;
class EntityType;
class RelationValueBase;
class Row;
class Storage;
class Table;

class RelationPrivate;
class Relation : public Property
{
    Q_OBJECT
public:
    //! \cond PRIVATE
    static const QString IdentifierColumn;
    static const QString IdentifierRightColumn;
    static const QString DisplayNameLeftColumn;
    static const QString DisplayNameRightColumn;
    static const QString EntityTypeLeftColumn;
    static const QString EntityTypeRightColumn;
    static const QString CardinalityColumn;
    static const QString TableNameColumn;
    static const QString ColumnNameColumn;
    static const QString ColumnNameRightColumn;
    static const QString EditableColumn;
    static const QString DirectionColumn;
    //! \endcond

    enum Cardinality {
        OneToOne,
        OneToMany,
        ManyToMany
    };

    enum Direction {
        LeftToRight,
        Both
    };

    ~Relation();

    int id() const;
    QString displayName() const;
    void setDisplayName(const QString &displayName);

    QString identifier() const;
    EntityType *entityType() const;
    EntityType *entityTypeOther() const;
    Cardinality cardinality() const;
    Direction direction() const;

    bool isEditable() const;
    bool isTranspose() const;

    Storage* storage() const;
    Row *row() const;

    Property::Type propertyType() const;

protected:
    friend class StoragePrivate;
    friend class RelationValueRightPrivate;
    friend class EntityTypePrivate;

    explicit Relation(Row *row, Storage *parent);
    explicit Relation(RelationPrivate &dd, Row *row, Storage *parent);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    QScopedPointer<RelationPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Relation)
    Q_DISABLE_COPY(Relation)
};

class TransposeRelation : public Relation
{
    Q_OBJECT
public:
    ~TransposeRelation();

private:
    friend class Relation;

    TransposeRelation(Relation *relation);

    Q_DECLARE_PRIVATE(Relation)
};

} // namespace LBDatabase

#endif // LBDATABASE_RELATION_H
