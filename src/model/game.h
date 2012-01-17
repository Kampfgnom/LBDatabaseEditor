#ifndef GAME_H
#define GAME_H

#include <LBDatabase/LBDatabase.h>

#include <QDateTime>

class Player;

class Game : public LBDatabase::Entity
{
    Q_OBJECT
public:
    Q_INVOKABLE Game(::LBDatabase::Row *row, ::LBDatabase::Context *context);

    static const QString Name;

    QString name() const;
    QDateTime date() const;
    QString comment() const;
    Entity *site() const;

    QList<Player *> players() const;
    QList<Player *> playersByPosition() const;

protected:
    mutable QList<Player *> m_players;
    mutable QList<Player *> m_playersByPosition;
};

class GamesContext : public LBDatabase::Context
{
    Q_OBJECT
public:
    Q_INVOKABLE GamesContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);

    static const QString Name;

    Game *game(int id) const;
};

#endif // GAME_H
