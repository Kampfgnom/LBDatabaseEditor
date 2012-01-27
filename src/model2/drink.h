#ifndef DRINK_H
#define DRINK_H

#include <LBDatabase/LBDatabase.h>


namespace DrinkProperties {
const QString NameAttribute("name");
const QString TypeAttribute("type");
const QString SizeAttribute("size");
const QString AlcAttribute("alc");
const QString IconPathAttribute("iconPath");
const QString LiveDrinksRelation("LiveDrinksPerDrink");
} // namespace DrinkProperties

class Livegamedrink;

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
	QIcon iconPath() const;

	QList<Livegamedrink *> liveDrinks() const;
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
