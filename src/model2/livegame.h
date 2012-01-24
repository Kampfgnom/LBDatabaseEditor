#ifndef LIVEGAME_H
#define LIVEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "game.h"

namespace LiveGameProperties {
}

class LiveGame : public Game
{
	Q_OBJECT
public:
	Q_INVOKABLE LiveGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

};

#endif // LIVEGAME_H
