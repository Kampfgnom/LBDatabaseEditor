#ifndef LIVEGAME_H
#define LIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "game.h"

namespace LiveGameProperties {
const QString PointsFunction("points");
} // namespace LiveGameProperties

class Player;

class LiveGame : public Game
{
	Q_OBJECT
public:
	Q_INVOKABLE LiveGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;


	int points(const Player *player) const;

};

#endif // LIVEGAME_H
