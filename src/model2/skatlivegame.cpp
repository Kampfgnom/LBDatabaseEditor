#include "skatlivegame.h"



const QString SkatLiveGame::Name("Skat Live Game");

SkatLiveGame::SkatLiveGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	LiveGame(row, context)
{
}

QString SkatLiveGame::skat_gameEnd() const
{
	return value(SkatLiveGameProperties::Skat_gameEndAttribute).value<QString>();
}

int SkatLiveGame::skat_maxPoints() const
{
	return value(SkatLiveGameProperties::Skat_maxPointsAttribute).value<int>();
}

int SkatLiveGame::skat_maxRounds() const
{
	return value(SkatLiveGameProperties::Skat_maxRoundsAttribute).value<int>();
}

bool SkatLiveGame::skat_mitRamschen() const
{
	return value(SkatLiveGameProperties::Skat_mitRamschenAttribute).value<bool>();
}

