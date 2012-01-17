#include "livegamecalculator.h"

#include "livegame.h"

LiveGameCalculator::LiveGameCalculator(QObject *parent) :
    GameCalculator(parent)
{
}

QVariant LiveGameCalculator::testAttribute(LBDatabase::Entity *entity)
{
    Game *game = static_cast<Game*>(entity);
    QVariant ret(QLatin1String("LiveGameCalculator::testAttribute ID: ")+QString::number(game->row()->id()));
    return ret;
}
