#ifndef ROUND_H
#define ROUND_H

#include <LBDatabase/LBDatabase.h>


namespace RoundProperties {
const QString NumberAttribute("number");
const QString CommentAttribute("comment");
const QString StartTimeAttribute("startTime");
const QString LengthAttribute("length");
const QString StateAttribute("state");
const QString DrinksRelation("DrinksPerRound");
const QString SchmeissereienRelation("SchmeissereienPerRound");
const QString GameRelation("RoundsPerGame");
const QString PointsFunction("points");
} // namespace RoundProperties

class Livegamedrink;
class Schmeisserei;
class LiveGame;
class Player;

class Round : public LBDatabase::Entity
{
	Q_OBJECT
public:
	Q_INVOKABLE Round(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	enum State {
		Running = 1,
		Paused = 2,
		Finished = 3
	};

	int number() const;
	QString comment() const;
	QDateTime startTime() const;
	QTime length() const;
	State state() const;


	int points(const Player *player) const;

	QList<Livegamedrink *> drinks() const;
	QList<Schmeisserei *> schmeissereien() const;
	LiveGame *game() const;

	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
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
