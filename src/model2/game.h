#ifndef GAME_H
#define GAME_H

#include <LBDatabase/LBDatabase.h>

namespace GameProperties {
const QString NameAttribute("name");
const QString DateAttribute("date");
const QString LengthAttribute("length");
const QString CommentAttribute("comment");
const QString RoundsPerGameRelation("RoundsPerGame");
const QString SiteIdRelation("siteId");
const QString GameIdRelation("gameId");
const QString PlayersByPositionRelation("playersByPosition");
}

class Round;class Place;class Dokoofflinegamebuddy;class Offlinegameinformation;class Player;class Game : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Game(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString name() const;
	QDateTime date() const;
	QTime length() const;
	QString comment() const;
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
