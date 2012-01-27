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
const QString SchmeissereienRelation("PlayerSchmeisserein");
const QString DrinksRelation("DrinksPerPlayer");
const QString HochzeitenRelation("DokoRoundHochzeitPlayer");
const QString Re1RoundsRelation("DokoRoundRe1Player");
const QString Re2RoundsRelation("DokoRoundRe2Player");
const QString SchweiereiRoundsRelation("DokoRoundSchweinereiPlayer");
const QString TrumpfabgabeRoundsRelation("DokoRoundTrumpfabgabePlayer");
const QString DokoSoliRelation("DokoRoundSoloPlayer");
const QString SkatSoliRelation("SkatRoundSolistPlayer");
const QString DokoBuddiesRelation("OfflineGameBuddy1");
const QString OfflineInformationRelation("OfflineInformationPerPlayer");
const QString PlaceRelation("PlayersAndPlaces");
} // namespace PlayerProperties

class Schmeisserei;
class Livegamedrink;
class DoppelkopfRound;
class SkatRound;
class Dokoofflinegamebuddy;
class Offlinegameinformation;
class Place;

class Player : public LBDatabase::Entity
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

	QList<Schmeisserei *> schmeissereien() const;
	QList<Livegamedrink *> drinks() const;
	QList<DoppelkopfRound *> hochzeiten() const;
	QList<DoppelkopfRound *> re1Rounds() const;
	QList<DoppelkopfRound *> re2Rounds() const;
	QList<DoppelkopfRound *> schweiereiRounds() const;
	QList<DoppelkopfRound *> trumpfabgabeRounds() const;
	QList<DoppelkopfRound *> dokoSoli() const;
	QList<SkatRound *> skatSoli() const;
    QList<Dokoofflinegamebuddy *> dokoBuddies() const;
	QList<Offlinegameinformation *> offlineInformation() const;
	QList<Place *> place() const;
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
