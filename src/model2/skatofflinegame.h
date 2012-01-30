#ifndef SKATOFFLINEGAME_H
#define SKATOFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace SkatOfflineGameProperties {
} // namespace SkatOfflineGameProperties


class SkatOfflineGame : public Offlinegame
{
	Q_OBJECT
public:
	Q_INVOKABLE SkatOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;




	// Write anything you want to remain unchanged between these comments: 
	//START



	// END
};

#endif // SKATOFFLINEGAME_H
