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
const QString PlayerRelation("OfflineInformationPerPlayer");
const QString GameRelation("OfflineInformationPerGame");
} // namespace OfflinegameinformationProperties

class Player;
class Game;

class Offlinegameinformation : public LBDatabase::Entity
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

	void setPlacement(int placement);
	void setPoints(int points);
	void setDoko_contrarounds(int doko_contrarounds);
	void setDoko_contrawins(int doko_contrawins);
	void setDoko_hochzeiten(int doko_hochzeiten);
	void setDoko_rerounds(int doko_rerounds);
	void setDoko_rewins(int doko_rewins);
	void setDoko_soli(int doko_soli);
	void setDoko_trumpfabgaben(int doko_trumpfabgaben);


	Player *player() const;
	Game *game() const;

	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
	void placementChanged(int placement);
	void pointsChanged(int points);
	void doko_contraroundsChanged(int doko_contrarounds);
	void doko_contrawinsChanged(int doko_contrawins);
	void doko_hochzeitenChanged(int doko_hochzeiten);
	void doko_reroundsChanged(int doko_rerounds);
	void doko_rewinsChanged(int doko_rewins);
	void doko_soliChanged(int doko_soli);
	void doko_trumpfabgabenChanged(int doko_trumpfabgaben);
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
