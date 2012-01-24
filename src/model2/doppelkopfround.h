#ifndef DOPPELKOPFROUND_H
#define DOPPELKOPFROUND_H

#include <LBDatabase/LBDatabase.h>

#include "round.h"

namespace DoppelkopfRoundProperties {
const QString Doko_soloPflichtAttribute("doko_soloPflicht");
const QString Doko_soloTypeAttribute("doko_soloType");
const QString Doko_hochzeitPlayerIdRelation("doko_hochzeitPlayerId");
const QString Doko_re1PlayerIdRelation("doko_re1PlayerId");
const QString Doko_re2PlayerIdRelation("doko_re2PlayerId");
const QString Doko_schweinereiPlayerIdRelation("doko_schweinereiPlayerId");
const QString Doko_trumpfabgabePlayerIdRelation("doko_trumpfabgabePlayerId");
const QString Doko_soloPlayerIdRelation("doko_soloPlayerId");
}

class Player;class Player;class Player;class Player;class Player;class Player;class DoppelkopfRound : public Round
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfRound(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	bool doko_soloPflicht() const;
	QString doko_soloType() const;
};

#endif // DOPPELKOPFROUND_H
