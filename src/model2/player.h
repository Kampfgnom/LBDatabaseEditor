#ifndef PLAYER_H
#define PLAYER_H

#include <LBDatabase/LBDatabase.h>

namespace PlayerProperties {
const QString WeightAttribute("weight");
const QString SizeAttribute("size");
const QString GenderAttribute("gender");
const QString NameAttribute("name");
const QString ColorAttribute("color");
const QString AvatarPathAttribute("avatarPath");
const QString PlayerSchmeissereinRelation("PlayerSchmeisserein");
const QString DrinksPerPlayerRelation("DrinksPerPlayer");
const QString Doko_hochzeitPlayerIdRelation("doko_hochzeitPlayerId");
const QString Doko_re1PlayerIdRelation("doko_re1PlayerId");
const QString Doko_re2PlayerIdRelation("doko_re2PlayerId");
const QString Doko_schweinereiPlayerIdRelation("doko_schweinereiPlayerId");
const QString Doko_trumpfabgabePlayerIdRelation("doko_trumpfabgabePlayerId");
const QString Doko_soloPlayerIdRelation("doko_soloPlayerId");
const QString Skat_solistPlayerIdRelation("skat_solistPlayerId");
const QString Player1IdRelation("player1Id");
const QString Player2IdRelation("player2Id");
const QString PlayerIdRelation("playerId");
const QString PlayerplaceassignmentsRelation("playerplaceassignments");
const QString PlayersByPositionRelation("playersByPosition");
}

class Schmeisserei;class Livegamedrink;class DoppelkopfRound;class DoppelkopfRound;class DoppelkopfRound;class DoppelkopfRound;class DoppelkopfRound;class DoppelkopfRound;class SkatRound;class Dokoofflinegamebuddy;class Dokoofflinegamebuddy;class Offlinegameinformation;class Place;class Game;class Player : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Player(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int weight() const;
	int size() const;
	QString gender() const;
	QString name() const;
	QColor color() const;
	QPixmap avatarPath() const;
};

class PlayersContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE PlayersContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Player *player(int id) const;
};

#endif // PLAYER_H
