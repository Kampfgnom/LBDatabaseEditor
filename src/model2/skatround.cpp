#include "skatround.h"

#include "player.h"


const QString SkatRound::Name("Skat Round");

SkatRound::SkatRound(LBDatabase::Row *row, LBDatabase::Context *context) :
	Round(row, context)
{
}

QString SkatRound::skat_gameType() const
{
	return value(SkatRoundProperties::Skat_gameTypeAttribute).value<QString>();
}

QString SkatRound::skat_trumpfColor() const
{
	return value(SkatRoundProperties::Skat_trumpfColorAttribute).value<QString>();
}

Player *SkatRound::skatSoloPlayer() const
{
	return relation<Player>(SkatRoundProperties::SkatSoloPlayerRelation)->firstEntity();
}

