#include "game.h"
#include <QDateTime>
#include <QTime>


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

QList<Round *> Game::rounds() const
{
	return relation<Round>(GameProperties::RoundsRelation)->entities();
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

GamesContext::GamesContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Game>();
	registerEntityClass<LiveGame>();
	registerCalculatorClass<LiveGame,LiveGameCalculator>();

	registerEntityClass<DoppelkopfLiveGame>();
	registerEntityClass<PrognoseOfflineGame>();
	registerEntityClass<OfflineGame>();
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

