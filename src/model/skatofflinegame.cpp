#include "skatofflinegame.h"



const QString SkatOfflineGame::Name("skatOfflineGame");

SkatOfflineGame::SkatOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	OfflineGame(row, context)
{
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString SkatOfflineGame::displayName() const
{
    return Entity::displayName();
}
	// END

