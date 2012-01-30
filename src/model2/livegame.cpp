#include "livegame.h"

#include "player.h"


const QString LiveGame::Name("Live Game");

LiveGame::LiveGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	Game(row, context)
{
}

int LiveGame::points(const Player *player) const
{
	return function(LiveGameProperties::PointsFunction)->value(player).value<int>();
}

