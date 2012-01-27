#ifndef SKATROUND_H
#define SKATROUND_H

#include <LBDatabase/LBDatabase.h>

#include "round.h"

namespace SkatRoundProperties {
const QString Skat_gameTypeAttribute("skat_gameType");
const QString Skat_trumpfColorAttribute("skat_trumpfColor");
const QString SkatSoloPlayerRelation("skatSoloPlayer");
}

class Player;

class SkatRound : public Round
{
	Q_OBJECT
public:
	Q_INVOKABLE SkatRound(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString skat_gameType() const;
	QString skat_trumpfColor() const;

	Player *skatSoloPlayer() const;
};

#endif // SKATROUND_H
