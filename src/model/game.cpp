#include "game.h"

#include "livegame.h"
#include "livegamecalculator.h"
#include "gamecalculator.h"

namespace {
const QString NameAttribute("name");
const QString DateAttribute("date");
const QString CommentAttribute("comment");
const QString SiteRelation("siteId");
const QString TestAttribute("testAttribute");
}

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
    return value(NameAttribute).toString();
}

QDateTime Game::date() const
{
    return value(DateAttribute).toDateTime();
}

QString Game::comment() const
{
    return value(CommentAttribute).toString();
}

LBDatabase::Entity *Game::site() const
{
    LBDatabase::RelationValue *v = static_cast<LBDatabase::RelationValue *>(propertyValue(entityType()->property(SiteRelation)));
    return v->firstEntity();
}

QString Game::testAttribute() const
{
    return value(TestAttribute).toString();
}
