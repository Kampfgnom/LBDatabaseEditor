#include "livegamecalculator.h"

#include "livegame.h"
#include "player.h"
#include "round.h"

LiveGameCalculator::LiveGameCalculator(QObject *parent) :
	Calculator(parent)
{
}

EntityVariantHash LiveGameCalculator::points(const LBDatabase::Entity *entity) const
{
    const LiveGame *liveGame = static_cast<const LiveGame *>(entity);

    EntityVariantHash result;
    foreach(Player *player, liveGame->players()) {
        foreach(Round *round, liveGame->rounds()) {
            result.insert(player, result.value(player, QVariant(0)).toInt() + round->points(player));
        }
    }

    return result;
}

// NEW METHODS HERE. DO NOT DELETE THIS LINE!
