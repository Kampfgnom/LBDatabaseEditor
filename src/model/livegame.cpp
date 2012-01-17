#include "livegame.h"

#include "player.h"
#include "round.h"

#include <QDebug>

namespace {
const QString RoundRelation("RoundsPerGame");
const QString PointsFunction("points");
}

const QString LiveGame::Name("Live Game");

LiveGame::LiveGame(LBDatabase::Row *row, LBDatabase::Context *context) :
    Game(row, context)
{
}

QList<Round *> LiveGame::rounds()
{
    if(!m_rounds.isEmpty())
        return m_rounds;

    LBDatabase::RelationValue *v = relation(RoundRelation);
    m_rounds = v->cast<Round>();
    return m_rounds;
}

int LiveGame::points(Player *player)
{
    LBDatabase::FunctionValue *pointsFunction = function(PointsFunction);
    return pointsFunction->value(player).toInt();
}
