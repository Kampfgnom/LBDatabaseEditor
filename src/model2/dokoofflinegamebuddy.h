#ifndef DOKOOFFLINEGAMEBUDDY_H
#define DOKOOFFLINEGAMEBUDDY_H

#include <LBDatabase/LBDatabase.h>


namespace DokoofflinegamebuddyProperties {
const QString RoundsAttribute("rounds");
const QString WinsAttribute("wins");
const QString GameRelation("DokoGameBuddiesPerGame");
const QString Player1Relation("OfflineGameBuddy1");
const QString Player2Relation("OfflineGameBuddy2");
} // namespace DokoofflinegamebuddyProperties

class Game;
class Player;

class Dokoofflinegamebuddy : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Dokoofflinegamebuddy(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int rounds() const;
	int wins() const;



	Game *game() const;
	Player *player1() const;
	Player *player2() const;

	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
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
