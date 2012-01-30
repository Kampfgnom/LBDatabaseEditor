#ifndef PROGNOSEOFFLINEGAME_H
#define PROGNOSEOFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace PrognoseOfflineGameProperties {
} // namespace PrognoseOfflineGameProperties


class PrognoseOfflineGame : public Offlinegame
{
	Q_OBJECT
public:
	Q_INVOKABLE PrognoseOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;



};

#endif // PROGNOSEOFFLINEGAME_H
