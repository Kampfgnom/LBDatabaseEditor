#include "round.h"

#include "livegamedrink.h"
#include "schmeisserei.h"
#include "livegame.h"
#include "player.h"
#include <QDateTime>
#include <QTime>


#include "doppelkopfround.h"
#include "skatround.h"

const QString RoundsContext::Name("rounds");
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

QList<Livegamedrink *> Round::drinks() const
{
	return relation<Livegamedrink>(RoundProperties::DrinksRelation)->entities();
}

QList<Schmeisserei *> Round::schmeissereien() const
{
	return relation<Schmeisserei>(RoundProperties::SchmeissereienRelation)->entities();
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

