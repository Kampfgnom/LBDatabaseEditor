#ifndef LBDATABASE_FUNCTION_H
#define LBDATABASE_FUNCTION_H

#include "property.h"

namespace LBDatabase {

class EntityType;
class Row;
class Storage;
class Table;

class FunctionPrivate;
class Function : public Property
{
public:
    static const QString IdentifierColumn;
    static const QString DisplayNameColumn;
    static const QString TableNameColumn;
    static const QString EntityColumnNameColumn;
    static const QString KeyEntityColumnNameColumn;
    static const QString ValueColumnNameColumn;
    static const QString EntityTypeColumn;
    static const QString KeyEntityTypeRightColumn;
    static const QString CalculatedColumn;
    static const QString CacheDataColumn;
    static const QString TypeColumn;
    static const QString EditableColumn;


    static const QString FunctionReimplementationsTable;
    static const QString ReimplementedFunctionColumn;
    static const QString ReimplementingEntityTypeColumn;

    ~Function();

    int id() const;
    QString displayName() const;
    void setDisplayName(const QString &displayName);
    QString identifier() const;

    EntityType *keyEntityType() const;
    QString qtTypeName() const;

    bool isCalculated() const;
    bool cacheData() const;
    bool isEditable() const;

    QList<EntityType *> reimplementingEntityTypes() const;

    Property::Type propertyType() const;

private:
    friend class StoragePrivate;
    friend class FunctionValue;

    explicit Function(Row *row, Storage *parent);

    void addReimplementingEntityType(EntityType *type);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    Table *functionTable() const;
    QString entityColumnName() const;
    QString keyEntityColumnName() const;
    QString valueColumnName() const;

    QScopedPointer<FunctionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Function)
    Q_DISABLE_COPY(Function)
};

} // namespace LBDatabase

#endif // LBDATABASE_FUNCTION_H
