#include "livegamedrink.h"

#include <QDateTime>


const QString LivegamedrinksContext::Name("livegamedrinks");
LivegamedrinksContext::LivegamedrinksContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Livegamedrink>();
}

Livegamedrink *LivegamedrinksContext::livegamedrink(int id) const
{
	return static_cast<Livegamedrink *>(entity(id));
}

const QString Livegamedrink::Name("livegamedrink");

Livegamedrink::Livegamedrink(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

QDateTime Livegamedrink::time() const
{
	return value(LivegamedrinkProperties::TimeAttribute).value<QDateTime>();
}

