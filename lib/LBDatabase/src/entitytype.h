#ifndef LBDATABASE_ENTITYTYPE_H
#define LBDATABASE_ENTITYTYPE_H

#include <QObject>

#include "attribute.h"
#include "relation.h"

namespace LBDatabase {

class Attribute;
class Calculator;
class Context;
class Entity;
class Function;
class Property;
class Row;
class Storage;

class EntityTypePrivate;
class EntityType : public QObject
{
    Q_OBJECT
public:
    //! \cond PRIVATE
    static const QString ContextColumn;
    static const QString NameColumn;
    static const QString ParentEntityTypeIdColumn;
    //! \endcond

    ~EntityType();

    int id() const;
    QString name() const;
    QString simplifiedName() const;
    void setName(const QString &name);
    Context *context() const;
    EntityType *parentEntityType() const;
    int parentEntityTypeId() const;

    QList<EntityType *> childEntityTypes() const;

    Property *property(const QString &name) const;

    QList<Property *> properties() const;
    QList<Attribute *> attributes() const;
    QList<Relation *> relations() const;
    QList<Function *> functions() const;

    QList<Property *> nonInhertitedProperties() const;
    QList<Attribute *> nonInhertitedAttributes() const;
    QList<Relation *> nonInhertitedRelations() const;
    QList<Function *> nonInhertitedFunctions() const;

    Attribute *addAttribute(const QString &name, Attribute::Type type);
    Relation *addRelation(const QString &name, EntityType *otherType, Relation::Cardinality cardinality);

    QList<Entity *> entities() const;

    bool inherits(EntityType *entityType) const;

    Calculator *calculator() const;

Q_SIGNALS:
    void nameChanged(QString name);

private:
    friend class ContextPrivate;
    friend class StoragePrivate;
    friend class AttributePrivate;
    friend class RelationPrivate;
    friend class EntityPrivate;
    friend class FunctionPrivate;

    explicit EntityType(LBDatabase::Row *row, Storage *parent);

    void setContext(Context *context);
    void addChildEntityType(EntityType *type);
    void setParentEntityType(EntityType *type);
    void addAttribute(Attribute *attribute);
    void addRelation(Relation *relation);
    void addFunction(Function *function);
    void inheritProperties(EntityType *parent);
    void inheritCalculator(EntityType *parent);
    void addEntity(Entity *entity);
    void setCalculator(Calculator *calculator);

    QScopedPointer<EntityTypePrivate> d_ptr;
    Q_DECLARE_PRIVATE(EntityType)
    Q_DISABLE_COPY(EntityType)
};

} // namespace LBDatabase

#endif // LBDATABASE_ENTITYTYPE_H
