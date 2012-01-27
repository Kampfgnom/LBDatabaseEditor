#ifndef DOPPELKOPFROUND_H
#define DOPPELKOPFROUND_H

#include <LBDatabase/LBDatabase.h>

#include "round.h"

namespace DoppelkopfRoundProperties {
const QString Doko_soloPflichtAttribute("doko_soloPflicht");
const QString Doko_soloTypeAttribute("doko_soloType");
const QString HochzeitPlayerRelation("hochzeitPlayer");
const QString _1RePlayerRelation("_1RePlayer");
const QString _2RePlayerRelation("_2RePlayer");
const QString SchweinereiPlayerRelation("schweinereiPlayer");
const QString TrumpfabgabePlayerRelation("trumpfabgabePlayer");
const QString DokoSoloPlayerRelation("dokoSoloPlayer");
}

class Player;
class Player;
class Player;
class Player;
class Player;
class Player;

class DoppelkopfRound : public Round
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfRound(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	bool doko_soloPflicht() const;
	QString doko_soloType() const;

	Player *hochzeitPlayer() const;
	Player *_1RePlayer() const;
	Player *_2RePlayer() const;
	Player *schweinereiPlayer() const;
	Player *trumpfabgabePlayer() const;
	Player *dokoSoloPlayer() const;
};

#endif // DOPPELKOPFROUND_H
