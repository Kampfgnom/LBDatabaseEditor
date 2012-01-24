#include "skatofflinegame.h"



const QString SkatOfflineGame::Name("Skat Offline Game");

SkatOfflineGame::SkatOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	OfflineGame(row, context)
{
}

