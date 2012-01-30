#include "livegamedrink.h"

#include "round.h"
#include "player.h"
#include "drink.h"



const QString LivegamedrinksContext::Name("livegamedrinks");
const QString Livegamedrink::Name("livegamedrink");

Livegamedrink::Livegamedrink(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

QDateTime Livegamedrink::time() const
{
	return value(LivegamedrinkProperties::TimeAttribute).value<QDateTime>();
}

void Livegamedrink::setTime(const QDateTime &time)
{
	if(time == this->time())
		return;
	setValue(LivegamedrinkProperties::TimeAttribute,QVariant::fromValue<QDateTime>(time));
	emit timeChanged(time);
}

Round *Livegamedrink::round() const
{
	return relation<Round>(LivegamedrinkProperties::RoundRelation)->firstEntity();
}

Player *Livegamedrink::player() const
{
	return relation<Player>(LivegamedrinkProperties::PlayerRelation)->firstEntity();
}

Drink *Livegamedrink::drink() const
{
	return relation<Drink>(LivegamedrinkProperties::DrinkRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

LivegamedrinksContext::LivegamedrinksContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Livegamedrink>();
}

Livegamedrink *LivegamedrinksContext::livegamedrink(int id) const
{
	return static_cast<Livegamedrink *>(entity(id));
}

