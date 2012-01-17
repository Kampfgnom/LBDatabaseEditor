#ifndef LBDATABASE_CALCULATOR_H
#define LBDATABASE_CALCULATOR_H

#include <QObject>

#include <QHash>

namespace LBDatabase {

class AttributeValue;
class Entity;
class FunctionValue;


class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = 0);
    
    QVariant calculate(Entity *entity, AttributeValue *attributeValue);

    QHash<Entity *, QVariant> calculate(Entity *entity, FunctionValue *functionValue);
    QVariant calculate(Entity *entity, FunctionValue *functionValue, Entity *key);
};

} // namespace LBDatabase

typedef QHash<LBDatabase::Entity *, QVariant> EntityVariantHash;

#endif // LBDATABASE_CALCULATOR_H
