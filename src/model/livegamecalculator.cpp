#include "livegamecalculator.h"

#include "livegame.h"
#include "player.h"
#include "round.h"

LiveGameCalculator::LiveGameCalculator(QObject *parent) :
    GameCalculator(parent)
{
}

EntityVariantHash LiveGameCalculator::points(LBDatabase::Entity *entity)
{
    QHash<LBDatabase::Entity *, QVariant> result;

    LiveGame *game = static_cast<LiveGame*>(entity);
    foreach(Player *player, game->players()) {
        foreach(Round *round, game->rounds()) {
            result.insert(player, result.value(player, QVariant(0)).toInt() + round->points(player));
        }
    }

    return result;
}
