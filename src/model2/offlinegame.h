#ifndef OFFLINEGAME_H
#define OFFLINEGAME_H

#include <LBDatabase/LBDatabase.h>

#include "game.h"

namespace OfflinegameProperties {
const QString Offline_lengthAttribute("offline_length");
} // namespace OfflinegameProperties


class Offlinegame : public Game
{
	Q_OBJECT
public:
	Q_INVOKABLE Offlinegame(::LBDatabase::Row *row, ::LBDatabase::Context *context);
	static const QString Name;

	QTime offline_length() const;


};

#endif // OFFLINEGAME_H
