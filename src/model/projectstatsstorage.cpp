#include "projectstatsstorage.h"

#include "game.h"
#include "player.h"
#include "round.h"

ProjectStatsStorage::ProjectStatsStorage(const QString &fileName, QObject *parent) :
    Storage(fileName, parent)
{
    registerContextType<GamesContext>();
    registerContextType<PlayersContext>();
    registerContextType<RoundsContext>();
}

GamesContext *ProjectStatsStorage::gamesContext() const
{
    return static_cast<GamesContext *>(context(GamesContext::Name));
}
