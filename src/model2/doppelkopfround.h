#ifndef DOPPELKOPFROUND_H
#define DOPPELKOPFROUND_H

#include <LBDatabase/LBDatabase.h>

#include "round.h"

namespace DoppelkopfRoundProperties {
const QString Doko_soloPflichtAttribute("doko_soloPflicht");
const QString Doko_soloTypeAttribute("doko_soloType");
const QString HochzeitPlayerRelation("DokoRoundHochzeitPlayer");
const QString RePlayer1Relation("DokoRoundRe1Player");
const QString RePlayer2Relation("DokoRoundRe2Player");
const QString SchweinereiPlayerRelation("DokoRoundSchweinereiPlayer");
const QString TrumpfabgabePlayerRelation("DokoRoundTrumpfabgabePlayer");
const QString DokoSoloPlayerRelation("DokoRoundSoloPlayer");
} // namespace DoppelkopfRoundProperties

class Player;

class DoppelkopfRound : public Round
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfRound(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	bool doko_soloPflicht() const;
	QString doko_soloType() const;

	void setDoko_soloPflicht(bool doko_soloPflicht);
	void setDoko_soloType(const QString &doko_soloType);


	Player *hochzeitPlayer() const;
	Player *rePlayer1() const;
	Player *rePlayer2() const;
	Player *schweinereiPlayer() const;
	Player *trumpfabgabePlayer() const;
	Player *dokoSoloPlayer() const;

	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
	void doko_soloPflichtChanged(bool doko_soloPflicht);
	void doko_soloTypeChanged(QString doko_soloType);
};

#endif // DOPPELKOPFROUND_H
