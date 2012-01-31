#include "player.h"

const QString PlayersContext::Name("players");
const QString Player::Name("player");

PlayersContext::PlayersContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
    Context(row, parent)
{
    registerEntityClass<Player>();
}

Player::Player(LBDatabase::Row *row, LBDatabase::Context *context) :
    Entity(row, context)
{
}

QString Player::displayName(int role) const
{
    Q_UNUSED(role);
    return value("name").toString();
}
