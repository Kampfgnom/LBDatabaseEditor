#ifndef DOKOOFFLINEGAMEBUDDY_H
#define DOKOOFFLINEGAMEBUDDY_H

#include <LBDatabase/LBDatabase.h>

namespace DokoofflinegamebuddyProperties {
const QString RoundsAttribute("rounds");
const QString WinsAttribute("wins");
const QString GameIdRelation("gameId");
const QString Player1IdRelation("player1Id");
const QString Player2IdRelation("player2Id");
}

class Game;class Player;class Player;class Dokoofflinegamebuddy : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Dokoofflinegamebuddy(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int rounds() const;
	int wins() const;
};

class DokoofflinegamebuddysContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE DokoofflinegamebuddysContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Dokoofflinegamebuddy *dokoofflinegamebuddy(int id) const;
};

#endif // DOKOOFFLINEGAMEBUDDY_H
