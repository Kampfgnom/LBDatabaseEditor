#include "round.h"

#include <QDateTime>
#include <QTime>

#include "doppelkopfround.h"
#include "skatround.h"

const QString RoundsContext::Name("rounds");
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

int Round::db_state() const
{
	return value(RoundProperties::Db_stateAttribute).value<int>();
}

