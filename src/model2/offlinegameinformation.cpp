#include "offlinegameinformation.h"



const QString OfflinegameinformationsContext::Name("offlinegameinformations");
OfflinegameinformationsContext::OfflinegameinformationsContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Offlinegameinformation>();
}

Offlinegameinformation *OfflinegameinformationsContext::offlinegameinformation(int id) const
{
	return static_cast<Offlinegameinformation *>(entity(id));
}

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

