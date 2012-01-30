#ifndef POKEROFFLINEGAME_H
#define POKEROFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace PokerOfflineGameProperties {
} // namespace PokerOfflineGameProperties


class PokerOfflineGame : public Offlinegame
{
	Q_OBJECT
public:
	Q_INVOKABLE PokerOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;




	// Write anything you want to remain unchanged between these comments: 
	//START



	// END
};

#endif // POKEROFFLINEGAME_H
