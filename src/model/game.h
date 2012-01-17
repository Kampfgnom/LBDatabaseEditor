#ifndef GAME_H
#define GAME_H

#include <LBDatabase/LBDatabase.h>

#include <QDateTime>

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

    QString testAttribute() const;
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
