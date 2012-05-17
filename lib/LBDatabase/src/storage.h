#ifndef LBDATABASE_STORAGE_H
#define LBDATABASE_STORAGE_H

#include <QObject>

#include <QMetaType>

namespace LBDatabase {

class Attribute;
class Context;
class Database;
class EntityType;
class Function;
class Relation;
class Table;

class StoragePrivate;
class Storage : public QObject
{
    Q_OBJECT
public:
    static Storage *instance(const QString &fileName);

    static void convertSqlliteDatabaseToStorage(const QString &sqliteDatabaseFileName, const QString &storageFileName);

    ~Storage();

    bool open();

    Database *database() const;
    QString name() const;
    void setName(const QString &name);
    QString fileName() const;
    QString sourcePath() const;

    Context *context(const QString name) const;

    QList<Context *> contexts() const;
    QList<EntityType *> entityTypes() const;

    Context *addContext(const QString &name, const QString &baseEntityTypeName);

Q_SIGNALS:
    void nameChanged(QString name);

protected:
    explicit Storage(const QString &fileName, QObject *parent = 0);

    template<class ContextClass>
    void registerContextType();

    Context *context(int id) const;
    EntityType *entityType(int id) const;
    Attribute *attribute(int id) const;

private:
    friend class EntityTypePrivate;
    friend class ContextPrivate;
    friend class EntityPrivate;
    friend class AttributePrivate;
    friend class RelationPrivate;
    friend class FunctionPrivate;
    friend class GraphvizExporter;
    friend class TransposeRelationPrivate;

    void insertEntityType(EntityType *type);
    void insertAttribute(Attribute *attribute);
    void insertRelation(Relation *relation);
    void insertFunction(Function *function);

    QList<Relation *> relations() const;

    Table *contextsTable() const;
    Table *entityTypesTable() const;
    Table *attributesTable() const;

    void registerContextType(const QString &contextName, QMetaObject metaObject);

    QScopedPointer<StoragePrivate> d_ptr;
    Q_DECLARE_PRIVATE(Storage)
    Q_DISABLE_COPY(Storage)
};

template<class ContextClass>
void Storage::registerContextType()
{
    registerContextType(ContextClass::Name, ContextClass::staticMetaObject);
}

} // namespace LBDatabase

Q_DECLARE_METATYPE(LBDatabase::Storage*)

#endif // LBDATABASE_STORAGE_H
