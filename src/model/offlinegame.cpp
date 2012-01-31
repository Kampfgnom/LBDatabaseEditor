#include "offlinegame.h"



const QString OfflineGame::Name("offlineGame");

OfflineGame::OfflineGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	Game(row, context)
{
}

QTime OfflineGame::offline_length() const
{
	return value(OfflineGameProperties::Offline_lengthAttribute).value<QTime>();
}

void OfflineGame::setOffline_length(const QTime &offline_length)
{
	if(offline_length == this->offline_length())
		return;
	setValue(OfflineGameProperties::Offline_lengthAttribute,QVariant::fromValue<QTime>(offline_length));
	emit offline_lengthChanged(offline_length);
}


	// Write anything you want to remain unchanged between these comments: 
	//START	// END

