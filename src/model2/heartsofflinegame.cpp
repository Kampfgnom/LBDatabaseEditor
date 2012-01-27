#include "heartsofflinegame.h"


const QString HeartsOfflineGame::Name("Hearts Offline Game");

HeartsOfflineGame::HeartsOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	OfflineGame(row, context)
{
}

