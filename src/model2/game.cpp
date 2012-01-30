#include "game.h"

#include "place.h"
#include "dokoofflinegamebuddy.h"
#include "offlinegameinformation.h"
#include "player.h"
#include <QDateTime>
#include <QTime>


#include "gamecalculator.h"
#include "livegame.h"
#include "livegamecalculator.h"
#include "doppelkopflivegame.h"
#include "prognoseofflinegame.h"
#include "offlinegame.h"
#include "doppelkopfofflinegame.h"
#include "skatlivegame.h"
#include "skatofflinegame.h"
#include "heartsofflinegame.h"
#include "pokerofflinegame.h"

const QString GamesContext::Name("games");
const QString Game::Name("game");

Game::Game(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

QString Game::name() const
{
	return value(GameProperties::NameAttribute).value<QString>();
}

QDateTime Game::date() const
{
	return value(GameProperties::DateAttribute).value<QDateTime>();
}

QTime Game::length() const
{
	return value(GameProperties::LengthAttribute).value<QTime>();
}

QString Game::comment() const
{
	return value(GameProperties::CommentAttribute).value<QString>();
}

Place *Game::site() const
{
	return relation<Place>(GameProperties::SiteRelation)->firstEntity();
}

QList<Dokoofflinegamebuddy *> Game::dokoBuddies() const
{
	return relation<Dokoofflinegamebuddy>(GameProperties::DokoBuddiesRelation)->entities();
}

QList<Offlinegameinformation *> Game::offlineInformation() const
{
	return relation<Offlinegameinformation>(GameProperties::OfflineInformationRelation)->entities();
}

QList<Player *> Game::players() const
{
	return relation<Player>(GameProperties::PlayersRelation)->entities();
}

int Game::position(const Player *player) const
{
	return function(GameProperties::PositionFunction)->value(player).value<int>();
}

int Game::placement(const Player *player) const
{
	return function(GameProperties::PlacementFunction)->value(player).value<int>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START

int Game::points(const Player *player) const
{
    Q_UNUSED(player);
    return 0;
}

	// END
GamesContext::GamesContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Game>();
	registerCalculatorClass<Game,GameCalculator>();

	registerEntityClass<LiveGame>();
	registerCalculatorClass<LiveGame,LiveGameCalculator>();

	registerEntityClass<DoppelkopfLiveGame>();
	registerEntityClass<PrognoseOfflineGame>();
	registerEntityClass<Offlinegame>();
	registerEntityClass<DoppelkopfOfflineGame>();
	registerEntityClass<SkatLiveGame>();
	registerEntityClass<SkatOfflineGame>();
	registerEntityClass<HeartsOfflineGame>();
	registerEntityClass<PokerOfflineGame>();
}

Game *GamesContext::game(int id) const
{
	return static_cast<Game *>(entity(id));
}

