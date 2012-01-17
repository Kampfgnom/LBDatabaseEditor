#include "game.h"

#include "livegame.h"
#include "livegamecalculator.h"
#include "gamecalculator.h"
#include "player.h"

#include <QDebug>

namespace {
const QString NameAttribute("name");
const QString DateAttribute("date");
const QString CommentAttribute("comment");
const QString SiteRelation("siteId");
const QString TestAttribute("testAttribute");
const QString PlayersRelation("playersByPosition");
const QString PositionFunction("position");
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
    Entity(row, context),
    m_players(QList<Player *>()),
    m_playersByPosition(QList<Player *>())
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
    LBDatabase::RelationValue *v =static_cast<LBDatabase::RelationValue *>(propertyValue(entityType()->property(SiteRelation)));
    return v->firstEntity();
}

QList<Player *> Game::players() const
{
    if(!m_players.isEmpty())
        return m_players;

    LBDatabase::RelationValue *v = relation(PlayersRelation);
    m_players = v->cast<Player>();
    return m_players;
}

QList<Player *> Game::playersByPosition() const
{
    if(!m_playersByPosition.isEmpty())
        return m_playersByPosition;

    LBDatabase::RelationValue *v = relation(PlayersRelation);
    LBDatabase::FunctionValue *positionFunction = function(PositionFunction);

    m_playersByPosition.reserve(v->entities().size());
    m_playersByPosition = v->sort<int, Player>(positionFunction);

    return m_playersByPosition;
}
