#ifndef POKEROFFLINEGAME_H
#define POKEROFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace PokerOfflineGameProperties {
}


class PokerOfflineGame : public OfflineGame
{
	Q_OBJECT
public:
	Q_INVOKABLE PokerOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;


};

#endif // POKEROFFLINEGAME_H
