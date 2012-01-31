#include "round.h"

#include "livedrink.h"
#include "schmeisserei.h"
#include "livegame.h"
#include "player.h"


#include "doppelkopfround.h"
#include "skatround.h"

const QString RoundsContext::Name("Rounds");
const QString Round::Name("round");

Round::Round(LBDatabase::Row *row, LBDatabase::Context *context) :
	Entity(row, context)
{
}

int Round::number() const
{
	return value(RoundProperties::NumberAttribute).value<int>();
}

QString Round::comment() const
{
	return value(RoundProperties::CommentAttribute).value<QString>();
}

QDateTime Round::startTime() const
{
	return value(RoundProperties::StartTimeAttribute).value<QDateTime>();
}

QTime Round::length() const
{
	return value(RoundProperties::LengthAttribute).value<QTime>();
}

Round::State Round::state() const
{
	return static_cast<State>(value(RoundProperties::StateAttribute).value<int>());
}

void Round::setNumber(int number)
{
	if(number == this->number())
		return;
	setValue(RoundProperties::NumberAttribute,QVariant::fromValue<int>(number));
	emit numberChanged(number);
}

void Round::setComment(const QString &comment)
{
	if(comment == this->comment())
		return;
	setValue(RoundProperties::CommentAttribute,QVariant::fromValue<QString>(comment));
	emit commentChanged(comment);
}

void Round::setStartTime(const QDateTime &startTime)
{
	if(startTime == this->startTime())
		return;
	setValue(RoundProperties::StartTimeAttribute,QVariant::fromValue<QDateTime>(startTime));
	emit startTimeChanged(startTime);
}

void Round::setLength(const QTime &length)
{
	if(length == this->length())
		return;
	setValue(RoundProperties::LengthAttribute,QVariant::fromValue<QTime>(length));
	emit lengthChanged(length);
}

void Round::setState(State state)
{
	if(state == this->state())
		return;
	setValue(RoundProperties::StateAttribute,QVariant::fromValue<int>(state));
	emit stateChanged(state);
}

QList<LiveDrink *> Round::liveDrinks() const
{
	return relation<LiveDrink>(RoundProperties::LiveDrinksRelation)->entities();
}

QList<Schmeisserei *> Round::schmeissereienPerRound() const
{
	return relation<Schmeisserei>(RoundProperties::SchmeissereienPerRoundRelation)->entities();
}

LiveGame *Round::game() const
{
	return relation<LiveGame>(RoundProperties::GameRelation)->firstEntity();
}

int Round::points(const Player *player) const
{
	return function(RoundProperties::PointsFunction)->value(player).value<int>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString Round::displayName() const
{
    return Entity::displayName();
}
	// END

RoundsContext::RoundsContext(LBDatabase::Row *row, LBDatabase::Storage *parent) :
	Context(row, parent)
{
	registerEntityClass<Round>();
	registerEntityClass<DoppelkopfRound>();
	registerEntityClass<SkatRound>();
}

Round *RoundsContext::round(int id) const
{
	return static_cast<Round *>(entity(id));
}

