#ifndef GAME_H
#define GAME_H

#include <LBDatabase/LBDatabase.h>

class Game : public LBDatabase::Entity
{
    Q_OBJECT
public:
    Q_INVOKABLE Game(::LBDatabase::Row *row, ::LBDatabase::Context *context);

private:
    Q_DISABLE_COPY(Game)
};

class GamesContext : public LBDatabase::Context
{
    Q_OBJECT
public:
    Q_INVOKABLE GamesContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);

private:
    Q_DISABLE_COPY(GamesContext)
};

Q_DECLARE_METATYPE(Game *)
Q_DECLARE_METATYPE(GamesContext *)

#endif // GAME_H
