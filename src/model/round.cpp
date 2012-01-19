#include "round.h"

#include "player.h"

namespace {
const QString PointsFunction("points");
}

const QString RoundsContext::Name("rounds");
const QString Round::Name("round");

RoundsContext::RoundsContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
    Context(row, parent)
{
    registerEntityClass<Round>();
}

Round::Round(LBDatabase::Row *row, LBDatabase::Context *context) :
    Entity(row, context)
{
}

int Round::points(Player *player)
{
    return function(PointsFunction)->value(player).toInt();
}
