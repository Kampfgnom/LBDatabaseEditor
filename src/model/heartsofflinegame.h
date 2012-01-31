#ifndef HEARTSOFFLINEGAME_H
#define HEARTSOFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace HeartsOfflineGameProperties {
} // namespace HeartsOfflineGameProperties


class HeartsOfflineGame : public OfflineGame
{
	Q_OBJECT
public:
	Q_INVOKABLE HeartsOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;





	// Write anything you want to remain unchanged between these comments: 
	//START	// END

signals:
};

#endif // HEARTSOFFLINEGAME_H
