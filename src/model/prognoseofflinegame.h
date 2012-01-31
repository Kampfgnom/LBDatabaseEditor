#ifndef PROGNOSEOFFLINEGAME_H
#define PROGNOSEOFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "offlinegame.h"

namespace PrognoseOfflineGameProperties {
} // namespace PrognoseOfflineGameProperties


class PrognoseOfflineGame : public OfflineGame
{
	Q_OBJECT
public:
	Q_INVOKABLE PrognoseOfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;





	// Write anything you want to remain unchanged between these comments: 
	//START	// END

signals:
};

#endif // PROGNOSEOFFLINEGAME_H
