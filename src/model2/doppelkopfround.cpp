#include "doppelkopfround.h"



const QString DoppelkopfRound::Name("Doppelkopf Round");

DoppelkopfRound::DoppelkopfRound(LBDatabase::Row *row, LBDatabase::Context *context) :
	Round(row, context)
{
}

bool DoppelkopfRound::doko_soloPflicht() const
{
	return value(DoppelkopfRoundProperties::Doko_soloPflichtAttribute).value<bool>();
}

QString DoppelkopfRound::doko_soloType() const
{
	return value(DoppelkopfRoundProperties::Doko_soloTypeAttribute).value<QString>();
}

