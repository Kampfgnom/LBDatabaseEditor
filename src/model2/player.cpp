#include "player.h"

#include <QColor>
#include <QPixmap>


const QString PlayersContext::Name("players");
PlayersContext::PlayersContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Player>();
}

Player *PlayersContext::player(int id) const
{
	return static_cast<Player *>(entity(id));
}

const QString Player::Name("player");

Player::Player(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Player::weight() const
{
	return value(PlayerProperties::WeightAttribute).value<int>();
}

int Player::size() const
{
	return value(PlayerProperties::SizeAttribute).value<int>();
}

QString Player::gender() const
{
	return value(PlayerProperties::GenderAttribute).value<QString>();
}

QString Player::name() const
{
	return value(PlayerProperties::NameAttribute).value<QString>();
}

QColor Player::color() const
{
	return value(PlayerProperties::ColorAttribute).value<QColor>();
}

QPixmap Player::avatarPath() const
{
	return value(PlayerProperties::AvatarPathAttribute).value<QPixmap>();
}

