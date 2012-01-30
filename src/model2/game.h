#ifndef GAME_H
#define GAME_H

#include <LBDatabase/LBDatabase.h>


namespace GameProperties {
const QString NameAttribute("name");
const QString DateAttribute("date");
const QString LengthAttribute("length");
const QString CommentAttribute("comment");
const QString SiteRelation("GameSite");
const QString DokoBuddiesRelation("DokoGameBuddiesPerGame");
const QString OfflineInformationRelation("OfflineInformationPerGame");
const QString PlayersRelation("PlayersPerGame");
const QString PositionFunction("position");
const QString PlacementFunction("placement");
} // namespace GameProperties

class Place;
class Dokoofflinegamebuddy;
class Offlinegameinformation;
class Player;

class Game : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Game(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString name() const;
	QDateTime date() const;
	QTime length() const;
	QString comment() const;


	int position(const Player *player) const;
	int placement(const Player *player) const;

	Place *site() const;
	QList<Dokoofflinegamebuddy *> dokoBuddies() const;
	QList<Offlinegameinformation *> offlineInformation() const;
	QList<Player *> players() const;

	// Write anything you want to remain unchanged between these comments: 
	//START

    virtual int points(const Player *player) const;

	// END

signals:
};

class GamesContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE GamesContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Game *game(int id) const;
};

#endif // GAME_H
