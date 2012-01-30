#ifndef LBDATABASE_ENUMATTRIBUTE_H
#define LBDATABASE_ENUMATTRIBUTE_H

#include "attribute.h"

#include <QHash>

namespace LBDatabase {

class EnumAttributePrivate;
class EnumAttribute : public LBDatabase::Attribute
{
    Q_OBJECT
public:
    static const QString EnumsTable;
    static const QString AttributeColumn;
    static const QString NameColumn;
    static const QString ValueColumn;

    QString typeName() const;
    QString qtType() const;

    QHash<int, QString> enumValues() const;

private:
    friend class StoragePrivate;
    EnumAttribute(Row *row, Storage *parent);

    void addEnumValue(const QString &name, int value);

    Q_DECLARE_PRIVATE(EnumAttribute);
};

} // namespace LBDatabase

#endif // LBDATABASE_ENUMATTRIBUTE_H
