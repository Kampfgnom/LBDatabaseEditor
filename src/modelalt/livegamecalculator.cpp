#include "livegamecalculator.h"

#include "livegame.h"
#include "player.h"
#include "round.h"

LiveGameCalculator::LiveGameCalculator(QObject *parent) :
    GameCalculator(parent)
{
}

EntityVariantHash LiveGameCalculator::points(const LBDatabase::Entity *entity)
{
    QHash<const LBDatabase::Entity *, QVariant> result;

    const LiveGame *game = static_cast<const LiveGame*>(entity);
    foreach(Player *player, game->players()) {
        foreach(Round *round, game->rounds()) {
            result.insert(player, result.value(player, QVariant(0)).toInt() + round->points(player));
        }
    }

    return result;
}
