#include "doppelkopfround.h"

#include "player.h"


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

void DoppelkopfRound::setDoko_soloPflicht(bool doko_soloPflicht)
{
	if(doko_soloPflicht == this->doko_soloPflicht())
		return;
	setValue(DoppelkopfRoundProperties::Doko_soloPflichtAttribute,QVariant::fromValue<bool>(doko_soloPflicht));
	emit doko_soloPflichtChanged(doko_soloPflicht);
}

void DoppelkopfRound::setDoko_soloType(const QString &doko_soloType)
{
	if(doko_soloType == this->doko_soloType())
		return;
	setValue(DoppelkopfRoundProperties::Doko_soloTypeAttribute,QVariant::fromValue<QString>(doko_soloType));
	emit doko_soloTypeChanged(doko_soloType);
}

Player *DoppelkopfRound::hochzeitPlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::HochzeitPlayerRelation)->firstEntity();
}

Player *DoppelkopfRound::rePlayer1() const
{
	return relation<Player>(DoppelkopfRoundProperties::RePlayer1Relation)->firstEntity();
}

Player *DoppelkopfRound::rePlayer2() const
{
	return relation<Player>(DoppelkopfRoundProperties::RePlayer2Relation)->firstEntity();
}

Player *DoppelkopfRound::schweinereiPlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::SchweinereiPlayerRelation)->firstEntity();
}

Player *DoppelkopfRound::trumpfabgabePlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::TrumpfabgabePlayerRelation)->firstEntity();
}

Player *DoppelkopfRound::dokoSoloPlayer() const
{
	return relation<Player>(DoppelkopfRoundProperties::DokoSoloPlayerRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

