#include "pokerofflinegame.h"


const QString PokerOfflineGame::Name("Poker Offline Game");

PokerOfflineGame::PokerOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	OfflineGame(row, context)
{
}

