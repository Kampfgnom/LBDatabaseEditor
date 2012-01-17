#ifndef LIVEGAMECALCULATOR_H
#define LIVEGAMECALCULATOR_H

#include "gamecalculator.h"

class LiveGameCalculator : public GameCalculator
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LiveGameCalculator(QObject *parent = 0);

    Q_INVOKABLE EntityVariantHash points(LBDatabase::Entity *entity);
};

#endif // LIVEGAMECALCULATOR_H
