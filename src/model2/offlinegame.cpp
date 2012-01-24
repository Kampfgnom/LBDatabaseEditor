#include "offlinegame.h"

#include <QTime>


const QString OfflineGame::Name("Offline Game");

OfflineGame::OfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	Game(row, context)
{
}

QTime OfflineGame::offline_length() const
{
	return value(OfflineGameProperties::Offline_lengthAttribute).value<QTime>();
}

