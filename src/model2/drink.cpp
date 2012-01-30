#include "drink.h"

#include "livegamedrink.h"
#include <QIcon>


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

QIcon Drink::iconPath() const
{
	return value(DrinkProperties::IconPathAttribute).value<QIcon>();
}

int Drink::drinkCount() const
{
	return value(DrinkProperties::DrinkCountAttribute).value<int>();
}

QList<Livegamedrink *> Drink::liveDrinks() const
{
	return relation<Livegamedrink>(DrinkProperties::LiveDrinksRelation)->entities();
}

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

