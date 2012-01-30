#ifndef ATTRIBUTE_P_H
#define ATTRIBUTE_P_H

#include "attribute.h"

namespace LBDatabase {

class AttributePrivate {
protected:
    AttributePrivate() {}

    virtual void init();
    void addPropertyValueToEntities();
    void addPropertyValue(Entity *entity);
    void fetchValues();

    Row *row;
    Storage *storage;
    QString name;
    QString displayName;
    EntityType *entityType;
    bool calculated;
    bool cacheData;

    Attribute::Type type;

    int columnIndex;

    Attribute * q_ptr;
    Q_DECLARE_PUBLIC(Attribute)
};

} // namespace LBDatabase

#endif // ATTRIBUTE_P_H
