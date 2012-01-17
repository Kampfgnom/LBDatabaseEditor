#ifndef GAMECALCULATOR_H
#define GAMECALCULATOR_H

#include <LBDatabase/LBDatabase.h>

#include <QVariant>

class Game;

class GameCalculator : public LBDatabase::Calculator
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit GameCalculator(QObject *parent = 0);
    
    Q_INVOKABLE QVariant testAttribute(LBDatabase::Entity *entity);
};

#endif // GAMECALCULATOR_H
