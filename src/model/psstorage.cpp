#include "psstorage.h"

#include "game.h"
#include "player.h"
#include "round.h"

PSStorage::PSStorage(const QString &fileName, QObject *parent) :
    Storage(fileName, parent)
{
    registerContextType<GamesContext>();
    registerContextType<PlayersContext>();
    registerContextType<RoundsContext>();
}

GamesContext *PSStorage::gamesContext() const
{
    return static_cast<GamesContext *>(context(GamesContext::Name));
}
