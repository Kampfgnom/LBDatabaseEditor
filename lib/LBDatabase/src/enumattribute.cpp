#include "enumattribute.h"

#include "attribute_p.h"
#include "database.h"
#include "entitytype.h"
#include "storage.h"

#include <QStringList>

namespace LBDatabase {

const QString EnumAttribute::EnumsTable("lbmeta_enums");
const QString EnumAttribute::AttributeColumn("attribute");
const QString EnumAttribute::NameColumn("name");
const QString EnumAttribute::ValueColumn("value");


class EnumAttributePrivate : public AttributePrivate {
    void init();

    QHash<int, QString> enumValues;

    Q_DECLARE_PUBLIC(EnumAttribute)
};

void EnumAttributePrivate::init()
{
    AttributePrivate::init();
}

EnumAttribute::EnumAttribute(Row *row, Storage *parent) :
    Attribute(*new EnumAttributePrivate, row, parent)
{
}

QString EnumAttribute::typeName() const
{
    Q_D(const EnumAttribute);
    return d->name;
}

QString EnumAttribute::qtType() const
{
    return typeName();
}

QHash<int, QString> EnumAttribute::enumValues() const
{
    Q_D(const EnumAttribute);
    return d->enumValues;
}

void EnumAttribute::addEnumValue(const QString &name, int value)
{
    Q_D(EnumAttribute);
    d->enumValues.insert(value, name);
}

} // namespace LBDatabase
