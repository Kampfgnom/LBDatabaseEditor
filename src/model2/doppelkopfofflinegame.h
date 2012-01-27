#ifndef DOPPELKOPFOFFLINEGAME_H
#define DOPPELKOPFOFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace DoppelkopfOfflineGameProperties {
} // namespace DoppelkopfOfflineGameProperties


class DoppelkopfOfflineGame : public OfflineGame
{
	Q_OBJECT
public:
	Q_INVOKABLE DoppelkopfOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;


};

#endif // DOPPELKOPFOFFLINEGAME_H
