#ifndef LIVEGAME_H
#define LIVEGAME_H

#include "game.h"

class Round;

namespace LiveGameProperties {
const QString RoundRelation("RoundsPerGame");
const QString PointsFunction("points");
}

class LiveGame : public Game
{
    Q_OBJECT
public:
    Q_INVOKABLE LiveGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);

    static const QString Name;

    QList<Round *> rounds() const;
    int points(Player *player) const;
    int placement(Player *player) const;
    QList<Player *> playersByPlacement() const;
};

#endif // LIVEGAME_H
