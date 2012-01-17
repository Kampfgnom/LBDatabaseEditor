#ifndef ROUND_H
#define ROUND_H

#include <LBDatabase/LBDatabase.h>

class Player;

class Round : public LBDatabase::Entity
{
    Q_OBJECT
public:
    Q_INVOKABLE Round(::LBDatabase::Row *row, ::LBDatabase::Context *context);

    static const QString Name;

    int points(Player *player);
};

class RoundsContext : public LBDatabase::Context
{
    Q_OBJECT
public:
    Q_INVOKABLE RoundsContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);

    static const QString Name;
};

#endif // ROUND_H
