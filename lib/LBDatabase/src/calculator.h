#ifndef LBDATABASE_CALCULATOR_H
#define LBDATABASE_CALCULATOR_H

#include <QObject>

namespace LBDatabase {

class AttributeValue;
class Entity;

class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = 0);
    
    QVariant calculate(Entity *entity, AttributeValue *attributeValue);
};

} // namespace LBDatabase

#endif // LBDATABASE_CALCULATOR_H
