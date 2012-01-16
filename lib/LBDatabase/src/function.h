#ifndef LBDATABASE_FUNCTION_H
#define LBDATABASE_FUNCTION_H

#include "property.h"

namespace LBDatabase {

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

    ~Function();

    virtual int id() const;
    virtual QString displayName(const Context *context = 0) const;
    virtual void setDisplayName(const QString &displayName, const Context *context = 0);

private:
    friend class StoragePrivate;
    friend class FunctionValue;

    explicit Function(Row *row, Storage *parent);

    virtual void addPropertyValueToEntities();
    virtual void addPropertyValue(Entity *entity);
    void fetchValues();

    QScopedPointer<FunctionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Function)
    Q_DISABLE_COPY(Function)
};

} // namespace LBDatabase

#endif // LBDATABASE_FUNCTION_H
