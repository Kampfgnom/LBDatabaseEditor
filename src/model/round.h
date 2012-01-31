#ifndef ROUND_H
#define ROUND_H

#include <LBDatabase/LBDatabase.h>

#include <QDateTime>
#include <QTime>

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

class LiveDrink;
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

	void setNumber(int number);
	void setComment(const QString &comment);
	void setStartTime(const QDateTime &startTime);
	void setLength(const QTime &length);
	void setState(State state);

	int points(const Player *player) const;

	QList<LiveDrink *> drinks() const;
	QList<Schmeisserei *> schmeissereien() const;
	LiveGame *game() const;

	// Write anything you want to remain unchanged between these comments: 
	//START	// END

signals:
	void numberChanged(int number);
	void commentChanged(QString comment);
	void startTimeChanged(QDateTime startTime);
	void lengthChanged(QTime length);
	void stateChanged(State state);
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
