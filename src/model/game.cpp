#include "game.h"

#include "livegame.h"
#include "livegamecalculator.h"
#include "gamecalculator.h"
#include "player.h"

#include <QDebug>

const QString GamesContext::Name("games");
const QString Game::Name("game");

GamesContext::GamesContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
    Context(row, parent)
{
    registerEntityClass<Game>();
    registerCalculatorClass<Game, GameCalculator>();

    registerEntityClass<LiveGame>();
    registerCalculatorClass<LiveGame, LiveGameCalculator>();
}

Game::Game(LBDatabase::Row *row, LBDatabase::Context *context) :
    Entity(row, context)
{
}

Game *GamesContext::game(int id) const
{
    return static_cast<Game *>(entity(id));
}

QString Game::name() const
{
    return value(GameProperties::NameAttribute).toString();
}

QDateTime Game::date() const
{
    return value(GameProperties::DateAttribute).toDateTime();
}

QString Game::comment() const
{
    return value(GameProperties::CommentAttribute).toString();
}

LBDatabase::Entity *Game::site() const
{
    return relation<Entity>(GameProperties::SiteRelation)->firstEntity();
}

QList<Player *> Game::players() const
{
    return relation<Player>(GameProperties::PlayersRelation)->entities();
}

QList<Player *> Game::playersByPosition() const
{
    return relation<Player>(GameProperties::PlayersRelation)->sort<int>(function(GameProperties::PositionFunction));
}

QList<Player *> Game::playersByPlacement() const
{
    return playersByPosition();
}
