#ifndef LIVEGAMEDRINK_H
#define LIVEGAMEDRINK_H

#include <LBDatabase/LBDatabase.h>


namespace LivegamedrinkProperties {
const QString TimeAttribute("time");
const QString RoundRelation("DrinksPerRound");
const QString PlayerRelation("LiveDrinksPerPlayer");
const QString DrinkRelation("LiveDrinksPerDrink");
} // namespace LivegamedrinkProperties

class Round;
class Player;
class Drink;

class Livegamedrink : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Livegamedrink(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QDateTime time() const;


	Round *round() const;
	Player *player() const;
	Drink *drink() const;
};

class LivegamedrinksContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE LivegamedrinksContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Livegamedrink *livegamedrink(int id) const;
};

#endif // LIVEGAMEDRINK_H
