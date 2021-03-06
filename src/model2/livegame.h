#ifndef LIVEGAME_H
#define LIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "game.h"

namespace LiveGameProperties {
const QString StateAttribute("state");
const QString RoundsRelation("RoundsPerGame");
const QString PointsFunction("points");
const QString PlacementFunction("placement");
} // namespace LiveGameProperties

class Round;
class Player;

class LiveGame : public Game
{
	Q_OBJECT
public:
	Q_INVOKABLE LiveGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	enum State {
		Running = 1,
		Paused = 2,
		Finished = 3
	};

	State state() const;


	int points(const Player *player) const;
	int placement(const Player *player) const;

	QList<Round *> rounds() const;

	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
};

#endif // LIVEGAME_H
