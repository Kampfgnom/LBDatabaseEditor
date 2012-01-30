#include "livegame.h"

#include "player.h"
#include "round.h"

#include <QDebug>

const QString LiveGame::Name("Live Game");

LiveGame::LiveGame(LBDatabase::Row *row, LBDatabase::Context *context) :
    Game(row, context)
{
}

QList<Round *> LiveGame::rounds() const
{
    return relation<Round>(LiveGameProperties::RoundRelation)->entities();
}

int LiveGame::points(Player *player) const
{
    return function(LiveGameProperties::PointsFunction)->value(player).toInt();
}

int LiveGame::placement(Player *player) const
{
    return playersByPlacement().indexOf(player) + 1;
}

QList<Player *> LiveGame::playersByPlacement() const
{
    return relation<Player>(GameProperties::PlayersRelation)->sort<int>(function(LiveGameProperties::PointsFunction), LBDatabase::SortDescending);
}
