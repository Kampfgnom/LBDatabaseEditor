#include "doppelkopfofflinegame.h"


const QString DoppelkopfOfflineGame::Name("Doppelkopf Offline Game");

DoppelkopfOfflineGame::DoppelkopfOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	OfflineGame(row, context)
{
}

