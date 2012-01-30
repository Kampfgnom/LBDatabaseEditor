#ifndef LBDATABASE_FUNCTION_H
#define LBDATABASE_FUNCTION_H

#include "property.h"

namespace LBDatabase {

class EntityType;
class Row;
class Storage;

class FunctionPrivate;
class Function : public Property
{
public:
    static const QString NameColumn;
    static const QString DisplayNameColumn;
    static const QString EntityTypeColumn;
    static const QString KeyEntityTypeRightColumn;
    static const QString CalculatedColumn;
    static const QString CacheDataColumn;
    static const QString TypeColumn;

    ~Function();

    int id() const;
    QString displayName(const Context *context = 0) const;
    void setDisplayName(const QString &displayName, const Context *context = 0);
    QString name() const;

    EntityType *keyEntityType() const;
    QString qtTypeName() const;

    bool isCalculated() const;
    bool cacheData() const;

private:
    friend class StoragePrivate;
    friend class FunctionValue;

    explicit Function(Row *row, Storage *parent);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    QScopedPointer<FunctionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Function)
    Q_DISABLE_COPY(Function)
};

} // namespace LBDatabase

#endif // LBDATABASE_FUNCTION_H
