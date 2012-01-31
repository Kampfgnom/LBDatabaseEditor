#ifndef OFFLINEGAME_H
#define OFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include <QTime>
#include "game.h"

namespace OfflineGameProperties {
const QString Offline_lengthAttribute("offline_length");
} // namespace OfflineGameProperties


class OfflineGame : public Game
{
	Q_OBJECT
public:
	Q_INVOKABLE OfflineGame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QString displayName() const;

	QTime offline_length() const;

	void setOffline_length(const QTime &offline_length);



	// Write anything you want to remain unchanged between these comments: 
	//START	// END

signals:
	void offline_lengthChanged(QTime offline_length);
};

#endif // OFFLINEGAME_H
