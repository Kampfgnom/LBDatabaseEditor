#include "gamecalculator.h"

#include "game.h"

GameCalculator::GameCalculator(QObject *parent) :
    LBDatabase::Calculator(parent)
{
}

QVariant GameCalculator::testAttribute(LBDatabase::Entity *entity)
{
    Game *game = static_cast<Game*>(entity);
    QVariant ret(QLatin1String("GameCalculator::testAttribute ID: ")+QString::number(game->row()->id()));
    return ret;
}
