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
};

#endif // GAMECALCULATOR_H
