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
    static const QString NameColumn;
    static const QString DisplayNameLeftColumn;
    static const QString DisplayNameRightColumn;
    static const QString EntityTypeLeftColumn;
    static const QString EntityTypeRightColumn;
    static const QString CardinalityColumn;
    static const QString ColumnOrTableNameColumn;
    //! \endcond

    enum Cardinality {
        OneToOne,
        OneToMany,
        ManyToMany
    };

    ~Relation();

    int id() const;
    QString displayName(const Context *context = 0) const;
    QString displayNameLeft() const;
    QString displayNameRight() const;
    void setDisplayName(const QString &displayName, const Context *context);

    QString name() const;
    EntityType *entityTypeLeft() const;
    EntityType *entityTypeRight() const;
    Cardinality cardinality() const;

    Storage* storage() const;

protected:
    friend class StoragePrivate;
    friend class RelationValueRightPrivate;
    friend class EntityTypePrivate;

    explicit Relation(Row *row, Storage *parent);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    virtual RelationValueBase *createLeftValue(Entity *entity);
    virtual RelationValueBase *createRightValue(Entity *entity);

    QScopedPointer<RelationPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Relation)
    Q_DISABLE_COPY(Relation)
};

} // namespace LBDatabase

#endif // LBDATABASE_RELATION_H
