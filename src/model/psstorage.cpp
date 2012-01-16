#include "psstorage.h"

#include "game.h"

PSStorage::PSStorage(const QString &fileName, QObject *parent) :
    Storage(fileName, parent)
{
    registerContextType<GamesContext>("games");
}
