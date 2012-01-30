#include "prognoseofflinegame.h"



const QString PrognoseOfflineGame::Name("Prognose Offline Game");

PrognoseOfflineGame::PrognoseOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	Offlinegame(row, context)
{
}

