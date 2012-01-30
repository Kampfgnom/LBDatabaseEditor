#ifndef DOPPELKOPFLIVEGAME_H
#define DOPPELKOPFLIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "livegame.h"

namespace DoppelkopfLiveGameProperties {
const QString Doko_mitHochzeitAttribute("doko_mitHochzeit");
const QString Doko_mitPflichtsoloAttribute("doko_mitPflichtsolo");
const QString Doko_mitSchmeissereiAttribute("doko_mitSchmeisserei");
const QString Doko_mitSchweinereiAttribute("doko_mitSchweinerei");
const QString Doko_mitSoloAttribute("doko_mitSolo");
const QString Doko_mitTrumpfabgabeAttribute("doko_mitTrumpfabgabe");
const QString Doko_mitBubensoloAttribute("doko_mitBubensolo");
const QString Doko_mitDamensoloAttribute("doko_mitDamensolo");
const QString Doko_mitFarbsoloAttribute("doko_mitFarbsolo");
const QString Doko_mitFleischlossAttribute("doko_mitFleischloss");
const QString Doko_mitFuenfKoenigeAttribute("doko_mitFuenfKoenige");
const QString Doko_mitNeunzigPunkteAttribute("doko_mitNeunzigPunkte");
const QString Doko_mitTrumpfabgabeSchmeissereiAttribute("doko_mitTrumpfabgabeSchmeisserei");
const QString Doko_mitTrumpfsoloAttribute("doko_mitTrumpfsolo");
const QString Doko_mitZuWenigTrumpfAttribute("doko_mitZuWenigTrumpf");
const QString Doko_mitFleischlosAttribute("doko_mitFleischlos");
const QString Doko_mitSchwarzsoloAttribute("doko_mitSchwarzsolo");
} // namespace DoppelkopfLiveGameProperties


class DoppelkopfLiveGame : public LiveGame
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfLiveGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	bool doko_mitHochzeit() const;
	bool doko_mitPflichtsolo() const;
	bool doko_mitSchmeisserei() const;
	bool doko_mitSchweinerei() const;
	bool doko_mitSolo() const;
	bool doko_mitTrumpfabgabe() const;
	bool doko_mitBubensolo() const;
	bool doko_mitDamensolo() const;
	bool doko_mitFarbsolo() const;
	bool doko_mitFleischloss() const;
	bool doko_mitFuenfKoenige() const;
	bool doko_mitNeunzigPunkte() const;
	bool doko_mitTrumpfabgabeSchmeisserei() const;
	bool doko_mitTrumpfsolo() const;
	bool doko_mitZuWenigTrumpf() const;
	bool doko_mitFleischlos() const;
	bool doko_mitSchwarzsolo() const;




	// Write anything you want to remain unchanged between these comments: 
	//START



	// END

signals:
};

#endif // DOPPELKOPFLIVEGAME_H
