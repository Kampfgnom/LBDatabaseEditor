#include "pokerofflinegame.h"



const QString PokerOfflineGame::Name("pokerOfflineGame");

PokerOfflineGame::PokerOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	OfflineGame(row, context)
{
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString PokerOfflineGame::displayName() const
{
    return Entity::displayName();
}
	// END

