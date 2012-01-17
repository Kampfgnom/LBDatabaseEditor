#ifndef LIVEGAME_H
#define LIVEGAME_H

#include "game.h"

class Round;

class LiveGame : public Game
{
    Q_OBJECT
public:
    Q_INVOKABLE LiveGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);

    static const QString Name;

    QList<Round *> rounds();

    int points(Player *player);

private:
    QList<Round *> m_rounds;
};

#endif // LIVEGAME_H
