#ifndef SCHMEISSEREI_H
#define SCHMEISSEREI_H

#include <LBDatabase/LBDatabase.h>


namespace SchmeissereiProperties {
const QString TypeAttribute("type");
const QString PlayerRelation("PlayerSchmeisserein");
const QString RoundRelation("SchmeissereienPerRound");
} // namespace SchmeissereiProperties

class Player;
class Round;

class Schmeisserei : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Schmeisserei(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int type() const;

	Player *player() const;
	Round *round() const;
};

class SchmeissereisContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE SchmeissereisContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Schmeisserei *schmeisserei(int id) const;
};

#endif // SCHMEISSEREI_H
