#include "livedrink.h"

#include "round.h"
#include "player.h"
#include "drink.h"



const QString LiveDrinksContext::Name("LiveDrinks");
const QString LiveDrink::Name("liveDrink");

LiveDrink::LiveDrink(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

QDateTime LiveDrink::time() const
{
	return value(LiveDrinkProperties::TimeAttribute).value<QDateTime>();
}

void LiveDrink::setTime(const QDateTime &time)
{
	if(time == this->time())
		return;
	setValue(LiveDrinkProperties::TimeAttribute,QVariant::fromValue<QDateTime>(time));
	emit timeChanged(time);
}

Round *LiveDrink::round() const
{
	return relation<Round>(LiveDrinkProperties::RoundRelation)->firstEntity();
}

Player *LiveDrink::player() const
{
	return relation<Player>(LiveDrinkProperties::PlayerRelation)->firstEntity();
}

Drink *LiveDrink::drink() const
{
	return relation<Drink>(LiveDrinkProperties::DrinkRelation)->firstEntity();
}


	// Write anything you want to remain unchanged between these comments: 
	//START	// END

LiveDrinksContext::LiveDrinksContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<LiveDrink>();
}

LiveDrink *LiveDrinksContext::liveDrink(int id) const
{
	return static_cast<LiveDrink *>(entity(id));
}

