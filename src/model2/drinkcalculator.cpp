#include "drinkcalculator.h"
#include "drink.h"

DrinkCalculator::DrinkCalculator(QObject *parent) :	Calculator(parent)
{
}

QVariant DrinkCalculator::drinkCount(const LBDatabase::Entity *entity) const
{
    const Drink *drink = static_cast<const Drink *>(entity);
    return QVariant(drink->liveDrinks().size());
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!
