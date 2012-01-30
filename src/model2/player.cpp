#include "player.h"

#include "schmeisserei.h"
#include "livegamedrink.h"
#include "doppelkopfround.h"
#include "skatround.h"
#include "dokoofflinegamebuddy.h"
#include "offlinegameinformation.h"
#include "place.h"
#include "game.h"
#include "drink.h"
#include <QColor>
#include <QPixmap>



const QString PlayersContext::Name("players");
const QString Player::Name("player");

Player::Player(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Player::weight() const
{
	return value(PlayerProperties::WeightAttribute).value<int>();
}

int Player::size() const
{
	return value(PlayerProperties::SizeAttribute).value<int>();
}

QString Player::gender() const
{
	return value(PlayerProperties::GenderAttribute).value<QString>();
}

QString Player::name() const
{
	return value(PlayerProperties::NameAttribute).value<QString>();
}

QColor Player::color() const
{
	return value(PlayerProperties::ColorAttribute).value<QColor>();
}

QPixmap Player::avatarPath() const
{
	return value(PlayerProperties::AvatarPathAttribute).value<QPixmap>();
}

QList<Schmeisserei *> Player::schmeissereien() const
{
	return relation<Schmeisserei>(PlayerProperties::SchmeissereienRelation)->entities();
}

QList<Livegamedrink *> Player::liveDrinks() const
{
	return relation<Livegamedrink>(PlayerProperties::LiveDrinksRelation)->entities();
}

QList<DoppelkopfRound *> Player::hochzeiten() const
{
	return relation<DoppelkopfRound>(PlayerProperties::HochzeitenRelation)->entities();
}

QList<DoppelkopfRound *> Player::re1Rounds() const
{
	return relation<DoppelkopfRound>(PlayerProperties::Re1RoundsRelation)->entities();
}

QList<DoppelkopfRound *> Player::re2Rounds() const
{
	return relation<DoppelkopfRound>(PlayerProperties::Re2RoundsRelation)->entities();
}

QList<DoppelkopfRound *> Player::schweiereiRounds() const
{
	return relation<DoppelkopfRound>(PlayerProperties::SchweiereiRoundsRelation)->entities();
}

QList<DoppelkopfRound *> Player::trumpfabgabeRounds() const
{
	return relation<DoppelkopfRound>(PlayerProperties::TrumpfabgabeRoundsRelation)->entities();
}

QList<DoppelkopfRound *> Player::dokoSoli() const
{
	return relation<DoppelkopfRound>(PlayerProperties::DokoSoliRelation)->entities();
}

QList<SkatRound *> Player::skatSoli() const
{
	return relation<SkatRound>(PlayerProperties::SkatSoliRelation)->entities();
}

QList<Dokoofflinegamebuddy *> Player::dokoBuddies1() const
{
	return relation<Dokoofflinegamebuddy>(PlayerProperties::DokoBuddies1Relation)->entities();
}

QList<Dokoofflinegamebuddy *> Player::dokoBuddies2() const
{
	return relation<Dokoofflinegamebuddy>(PlayerProperties::DokoBuddies2Relation)->entities();
}

QList<Offlinegameinformation *> Player::offlineInformation() const
{
	return relation<Offlinegameinformation>(PlayerProperties::OfflineInformationRelation)->entities();
}

QList<Place *> Player::place() const
{
	return relation<Place>(PlayerProperties::PlaceRelation)->entities();
}

QList<Game *> Player::games() const
{
	return relation<Game>(PlayerProperties::GamesRelation)->entities();
}

QList<Drink *> Player::drinks() const
{
	return relation<Drink>(PlayerProperties::DrinksRelation)->entities();
}

PlayersContext::PlayersContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Player>();
}

Player *PlayersContext::player(int id) const
{
	return static_cast<Player *>(entity(id));
}

