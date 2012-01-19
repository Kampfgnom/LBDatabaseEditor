#ifndef PLAYER_H
#define PLAYER_H

#include <LBDatabase/LBDatabase.h>

class Player : public LBDatabase::Entity
{
    Q_OBJECT
public:
    Q_INVOKABLE Player(::LBDatabase::Row *row, ::LBDatabase::Context *context);

    QString displayName(int role = Qt::DisplayRole) const;

    static const QString Name;
};

class PlayersContext : public LBDatabase::Context
{
    Q_OBJECT
public:
    Q_INVOKABLE PlayersContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);

    static const QString Name;
};

#endif // PLAYER_H
