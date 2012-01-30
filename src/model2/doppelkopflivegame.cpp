#include "doppelkopflivegame.h"



const QString DoppelkopfLiveGame::Name("Doppelkopf Live Game");

DoppelkopfLiveGame::DoppelkopfLiveGame(LBDatabase::Row *row, LBDatabase::Context *context) :
	LiveGame(row, context)
{
}

bool DoppelkopfLiveGame::doko_mitHochzeit() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitHochzeitAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitPflichtsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitPflichtsoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSchmeisserei() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSchmeissereiAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSchweinerei() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSchweinereiAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitTrumpfabgabe() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitTrumpfabgabeAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitBubensolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitBubensoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitDamensolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitDamensoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFarbsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFarbsoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFleischloss() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFleischlossAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFuenfKoenige() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFuenfKoenigeAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitNeunzigPunkte() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitNeunzigPunkteAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitTrumpfabgabeSchmeisserei() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitTrumpfabgabeSchmeissereiAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitTrumpfsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitTrumpfsoloAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitZuWenigTrumpf() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitZuWenigTrumpfAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitFleischlos() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitFleischlosAttribute).value<bool>();
}

bool DoppelkopfLiveGame::doko_mitSchwarzsolo() const
{
	return value(DoppelkopfLiveGameProperties::Doko_mitSchwarzsoloAttribute).value<bool>();
}


	// Write anything you want to remain unchanged between these comments: 
	//START



	// END
