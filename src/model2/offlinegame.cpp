#include "offlinegame.h"



const QString Offlinegame::Name("offlinegame");

Offlinegame::Offlinegame(LBDatabase::Row *row, LBDatabase::Context *context) :
	Game(row, context)
{
}

QTime Offlinegame::offline_length() const
{
	return value(OfflinegameProperties::Offline_lengthAttribute).value<QTime>();
}

void Offlinegame::setOffline_length(const QTime &offline_length)
{
	if(offline_length == this->offline_length())
		return;
	setValue(OfflinegameProperties::Offline_lengthAttribute,QVariant::fromValue<QTime>(offline_length));
	emit offline_lengthChanged(offline_length);
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

