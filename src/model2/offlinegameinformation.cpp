#include "offlinegameinformation.h"

#include "player.h"
#include "game.h"



const QString OfflinegameinformationsContext::Name("offlinegameinformations");
const QString Offlinegameinformation::Name("offlinegameinformation");

Offlinegameinformation::Offlinegameinformation(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Offlinegameinformation::placement() const
{
	return value(OfflinegameinformationProperties::PlacementAttribute).value<int>();
}

int Offlinegameinformation::points() const
{
	return value(OfflinegameinformationProperties::PointsAttribute).value<int>();
}

int Offlinegameinformation::doko_contrarounds() const
{
	return value(OfflinegameinformationProperties::Doko_contraroundsAttribute).value<int>();
}

int Offlinegameinformation::doko_contrawins() const
{
	return value(OfflinegameinformationProperties::Doko_contrawinsAttribute).value<int>();
}

int Offlinegameinformation::doko_hochzeiten() const
{
	return value(OfflinegameinformationProperties::Doko_hochzeitenAttribute).value<int>();
}

int Offlinegameinformation::doko_rerounds() const
{
	return value(OfflinegameinformationProperties::Doko_reroundsAttribute).value<int>();
}

int Offlinegameinformation::doko_rewins() const
{
	return value(OfflinegameinformationProperties::Doko_rewinsAttribute).value<int>();
}

int Offlinegameinformation::doko_soli() const
{
	return value(OfflinegameinformationProperties::Doko_soliAttribute).value<int>();
}

int Offlinegameinformation::doko_trumpfabgaben() const
{
	return value(OfflinegameinformationProperties::Doko_trumpfabgabenAttribute).value<int>();
}

void Offlinegameinformation::setPlacement(int placement)
{
	if(placement == this->placement())
		return;
	setValue(OfflinegameinformationProperties::PlacementAttribute,QVariant::fromValue<int>(placement));
	emit placementChanged(placement);
}

void Offlinegameinformation::setPoints(int points)
{
	if(points == this->points())
		return;
	setValue(OfflinegameinformationProperties::PointsAttribute,QVariant::fromValue<int>(points));
	emit pointsChanged(points);
}

void Offlinegameinformation::setDoko_contrarounds(int doko_contrarounds)
{
	if(doko_contrarounds == this->doko_contrarounds())
		return;
	setValue(OfflinegameinformationProperties::Doko_contraroundsAttribute,QVariant::fromValue<int>(doko_contrarounds));
	emit doko_contraroundsChanged(doko_contrarounds);
}

void Offlinegameinformation::setDoko_contrawins(int doko_contrawins)
{
	if(doko_contrawins == this->doko_contrawins())
		return;
	setValue(OfflinegameinformationProperties::Doko_contrawinsAttribute,QVariant::fromValue<int>(doko_contrawins));
	emit doko_contrawinsChanged(doko_contrawins);
}

void Offlinegameinformation::setDoko_hochzeiten(int doko_hochzeiten)
{
	if(doko_hochzeiten == this->doko_hochzeiten())
		return;
	setValue(OfflinegameinformationProperties::Doko_hochzeitenAttribute,QVariant::fromValue<int>(doko_hochzeiten));
	emit doko_hochzeitenChanged(doko_hochzeiten);
}

void Offlinegameinformation::setDoko_rerounds(int doko_rerounds)
{
	if(doko_rerounds == this->doko_rerounds())
		return;
	setValue(OfflinegameinformationProperties::Doko_reroundsAttribute,QVariant::fromValue<int>(doko_rerounds));
	emit doko_reroundsChanged(doko_rerounds);
}

void Offlinegameinformation::setDoko_rewins(int doko_rewins)
{
	if(doko_rewins == this->doko_rewins())
		return;
	setValue(OfflinegameinformationProperties::Doko_rewinsAttribute,QVariant::fromValue<int>(doko_rewins));
	emit doko_rewinsChanged(doko_rewins);
}

void Offlinegameinformation::setDoko_soli(int doko_soli)
{
	if(doko_soli == this->doko_soli())
		return;
	setValue(OfflinegameinformationProperties::Doko_soliAttribute,QVariant::fromValue<int>(doko_soli));
	emit doko_soliChanged(doko_soli);
}

void Offlinegameinformation::setDoko_trumpfabgaben(int doko_trumpfabgaben)
{
	if(doko_trumpfabgaben == this->doko_trumpfabgaben())
		return;
	setValue(OfflinegameinformationProperties::Doko_trumpfabgabenAttribute,QVariant::fromValue<int>(doko_trumpfabgaben));
	emit doko_trumpfabgabenChanged(doko_trumpfabgaben);
}

Player *Offlinegameinformation::player() const
{
	return relation<Player>(OfflinegameinformationProperties::PlayerRelation)->firstEntity();
}

Game *Offlinegameinformation::game() const
{
	return relation<Game>(OfflinegameinformationProperties::GameRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

OfflinegameinformationsContext::OfflinegameinformationsContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Offlinegameinformation>();
}

Offlinegameinformation *OfflinegameinformationsContext::offlinegameinformation(int id) const
{
	return static_cast<Offlinegameinformation *>(entity(id));
}

