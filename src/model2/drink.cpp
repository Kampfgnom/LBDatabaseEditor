#include "drink.h"

#include "livegamedrink.h"
#include "player.h"


#include "drinkcalculator.h"

const QString DrinksContext::Name("drinks");
const QString Drink::Name("Drink");

Drink::Drink(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

QString Drink::name() const
{
	return value(DrinkProperties::NameAttribute).value<QString>();
}

QString Drink::type() const
{
	return value(DrinkProperties::TypeAttribute).value<QString>();
}

double Drink::size() const
{
	return value(DrinkProperties::SizeAttribute).value<double>();
}

double Drink::alc() const
{
	return value(DrinkProperties::AlcAttribute).value<double>();
}

QIcon Drink::icon() const
{
	return value(DrinkProperties::IconAttribute).value<QIcon>();
}

int Drink::drinkCount() const
{
	return value(DrinkProperties::DrinkCountAttribute).value<int>();
}

QString Drink::mostDrinks() const
{
	return value(DrinkProperties::MostDrinksAttribute).value<QString>();
}

void Drink::setName(const QString &name)
{
	if(name == this->name())
		return;
	setValue(DrinkProperties::NameAttribute,QVariant::fromValue<QString>(name));
	emit nameChanged(name);
}

void Drink::setType(const QString &type)
{
	if(type == this->type())
		return;
	setValue(DrinkProperties::TypeAttribute,QVariant::fromValue<QString>(type));
	emit typeChanged(type);
}

void Drink::setSize(double size)
{
	if(size == this->size())
		return;
	setValue(DrinkProperties::SizeAttribute,QVariant::fromValue<double>(size));
	emit sizeChanged(size);
}

void Drink::setAlc(double alc)
{
	if(alc == this->alc())
		return;
	setValue(DrinkProperties::AlcAttribute,QVariant::fromValue<double>(alc));
	emit alcChanged(alc);
}

QList<Livegamedrink *> Drink::liveDrinks() const
{
	return relation<Livegamedrink>(DrinkProperties::LiveDrinksRelation)->entities();
}

QList<Player *> Drink::players() const
{
	return relation<Player>(DrinkProperties::PlayersRelation)->entities();
}

int Drink::countPerPlayer(const Player *player) const
{
	return function(DrinkProperties::CountPerPlayerFunction)->value(player).value<int>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

DrinksContext::DrinksContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Drink>();
	registerCalculatorClass<Drink,DrinkCalculator>();

}

Drink *DrinksContext::drink(int id) const
{
	return static_cast<Drink *>(entity(id));
}

