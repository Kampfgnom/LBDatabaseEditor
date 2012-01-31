#include "prognoseofflinegame.h"



const QString PrognoseOfflineGame::Name("prognoseOfflineGame");

PrognoseOfflineGame::PrognoseOfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	OfflineGame(row, context)
{
}


	// Write anything you want to remain unchanged between these comments: 
	//START
QString PrognoseOfflineGame::displayName() const
{
    return Entity::displayName();
}
	// END

