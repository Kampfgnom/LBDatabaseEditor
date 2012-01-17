#include "psstorage.h"

#include "game.h"

PSStorage::PSStorage(const QString &fileName, QObject *parent) :
    Storage(fileName, parent)
{
    registerContextType<GamesContext>();
}

GamesContext *PSStorage::gamesContext() const
{
    return static_cast<GamesContext *>(context(GamesContext::Name));
}
