#ifndef SKATOFFLINEGAME_H
#define SKATOFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace SkatOfflineGameProperties {
} // namespace SkatOfflineGameProperties


class SkatOfflineGame : public OfflineGame
{
	Q_OBJECT
public:
	Q_INVOKABLE SkatOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;





	// Write anything you want to remain unchanged between these comments: 
	//START	// END

signals:
};

#endif // SKATOFFLINEGAME_H