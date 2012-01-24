#include "livegame.h"



const QString LiveGame::Name("Live Game");

LiveGame::LiveGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	Game(row, context)
{
}

