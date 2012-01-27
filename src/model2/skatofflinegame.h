#ifndef SKATOFFLINEGAME_H
#define SKATOFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace SkatOfflineGameProperties {
}


class SkatOfflineGame : public OfflineGame
{
	Q_OBJECT
public:
	Q_INVOKABLE SkatOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;


};

#endif // SKATOFFLINEGAME_H
