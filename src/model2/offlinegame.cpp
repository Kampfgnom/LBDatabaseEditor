#include "offlinegame.h"

#include <QTime>


const QString Offlinegame::Name("offlinegame");

Offlinegame::Offlinegame(LBDatabase::Row *row, LBDatabase::Context *context) :
	Game(row, context)
{
}

QTime Offlinegame::offline_length() const
{
	return value(OfflinegameProperties::Offline_lengthAttribute).value<QTime>();
}

