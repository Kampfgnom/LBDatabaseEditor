#ifndef SKATLIVEGAME_H
#define SKATLIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "livegame.h"

namespace SkatLiveGameProperties {
const QString Skat_gameEndAttribute("skat_gameEnd");
const QString Skat_maxPointsAttribute("skat_maxPoints");
const QString Skat_maxRoundsAttribute("skat_maxRounds");
const QString Skat_mitRamschenAttribute("skat_mitRamschen");
}


class SkatLiveGame : public LiveGame
{
	Q_OBJECT
public:
	Q_INVOKABLE SkatLiveGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString skat_gameEnd() const;
	int skat_maxPoints() const;
	int skat_maxRounds() const;
	bool skat_mitRamschen() const;

};

#endif // SKATLIVEGAME_H
