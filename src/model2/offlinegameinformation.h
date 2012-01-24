#ifndef OFFLINEGAMEINFORMATION_H
#define OFFLINEGAMEINFORMATION_H

#include <LBDatabase/LBDatabase.h>

namespace OfflinegameinformationProperties {
const QString PlacementAttribute("placement");
const QString PointsAttribute("points");
const QString Doko_contraroundsAttribute("doko_contrarounds");
const QString Doko_contrawinsAttribute("doko_contrawins");
const QString Doko_hochzeitenAttribute("doko_hochzeiten");
const QString Doko_reroundsAttribute("doko_rerounds");
const QString Doko_rewinsAttribute("doko_rewins");
const QString Doko_soliAttribute("doko_soli");
const QString Doko_trumpfabgabenAttribute("doko_trumpfabgaben");
const QString PlayerIdRelation("playerId");
const QString GameIdRelation("gameId");
}

class Player;class Game;class Offlinegameinformation : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Offlinegameinformation(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int placement() const;
	int points() const;
	int doko_contrarounds() const;
	int doko_contrawins() const;
	int doko_hochzeiten() const;
	int doko_rerounds() const;
	int doko_rewins() const;
	int doko_soli() const;
	int doko_trumpfabgaben() const;
};

class OfflinegameinformationsContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE OfflinegameinformationsContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Offlinegameinformation *offlinegameinformation(int id) const;
};

#endif // OFFLINEGAMEINFORMATION_H
