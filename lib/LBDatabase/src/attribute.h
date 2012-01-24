#ifndef LBDATABASE_ATTRIBUTE_H
#define LBDATABASE_ATTRIBUTE_H

#include "property.h"

namespace LBDatabase {

class EntityType;
class Row;
class Storage;

class AttributePrivate;
class Attribute : public Property
{
    Q_OBJECT
public:
    static const QString NameColumn;
    static const QString DisplayNameColumn;
    static const QString EntityTypeIdColumn;
    static const QString CalculatedColumn;
    static const QString CacheDataColumn;
    static const QString TypeColumn;

    enum Type {
        Unkown,     // 0
        Text,       // 1
        Integer,    // 2
        Real,       // 3
        Icon,       // 4
        Pixmap,     // 5
        DateTime,   // 6
        Time,       // 7
        Bool,       // 8
        Color       // 9
    };

    ~Attribute();

    int id() const;
    QString displayName(const Context *context = 0) const;
    virtual void setDisplayName(const QString &displayName, const Context *context = 0);
    int columnIndex() const;

    QString name() const;

    bool isCalculated() const;
    bool cacheData() const;

    Type type() const;
    QString typeName() const;
    static QString typeToName(Type type);
    static QStringList typeNames();

    QString qtType() const;
    static QStringList qtTypeNames();
    static QString typeToQtType(Type type);

private:
    friend class StoragePrivate;
    friend class EntityTypePrivate;

    explicit Attribute(Row *row, Storage *parent);

    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);

    void fetchValues();

    QScopedPointer<AttributePrivate> d_ptr;
    Q_DECLARE_PRIVATE(Attribute)
    Q_DISABLE_COPY(Attribute)
};

} // namespace LBDatabase

#endif // LBDATABASE_ATTRIBUTE_H
