#ifndef ROUND_H
#define ROUND_H

#include <LBDatabase/LBDatabase.h>

namespace RoundProperties {
const QString NumberAttribute("number");
const QString CommentAttribute("comment");
const QString StartTimeAttribute("startTime");
const QString LengthAttribute("length");
const QString Db_stateAttribute("db_state");
const QString DrinksPerRoundRelation("DrinksPerRound");
const QString SchmeissereienPerRoundRelation("SchmeissereienPerRound");
const QString RoundsPerGameRelation("RoundsPerGame");
}

class Livegamedrink;class Schmeisserei;class Game;class Round : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Round(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	int number() const;
	QString comment() const;
	QDateTime startTime() const;
	QTime length() const;
	int db_state() const;
};

class RoundsContext : public LBDatabase::Context
{
	Q_OBJECT
public:
	Q_INVOKABLE RoundsContext(::LBDatabase::Row *row, ::LBDatabase::Storage *parent);
	static const QString Name;

	Round *round(int id) const;
};

#endif // ROUND_H
