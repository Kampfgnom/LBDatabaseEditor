#ifndef DRINK_H
#define DRINK_H

#include <LBDatabase/LBDatabase.h>


namespace DrinkProperties {
const QString NameAttribute("name");
const QString TypeAttribute("type");
const QString SizeAttribute("size");
const QString AlcAttribute("alc");
const QString IconAttribute("icon");
const QString DrinkCountAttribute("drinkCount");
const QString MostDrinksAttribute("mostDrinks");
const QString LiveDrinksRelation("LiveDrinksPerDrink");
const QString PlayersRelation("DrinksPerPlayer");
const QString CountPerPlayerFunction("countPerPlayer");
} // namespace DrinkProperties

class Livegamedrink;
class Player;

class Drink : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Drink(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString name() const;
	QString type() const;
	double size() const;
	double alc() const;
	QIcon icon() const;
	int drinkCount() const;
	QString mostDrinks() const;

	void setName(const QString &name);
	void setType(const QString &type);
	void setSize(double size);
	void setAlc(double alc);

	int countPerPlayer(const Player *player) const;

	QList<Livegamedrink *> liveDrinks() const;
	QList<Player *> players() const;

	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
	void nameChanged(QString name);
	void typeChanged(QString type);
	void sizeChanged(double size);
	void alcChanged(double alc);
};

class DrinksContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE DrinksContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Drink *drink(int id) const;
};

#endif // DRINK_H
