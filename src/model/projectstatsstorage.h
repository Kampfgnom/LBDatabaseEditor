#ifndef PSSTORAGE_H
#define PSSTORAGE_H

#include <LBDatabase/LBDatabase.h>

class GamesContext;

class ProjectStatsStorage : public LBDatabase::Storage
{
public:
    ProjectStatsStorage(const QString &fileName, QObject *parent = 0);

    GamesContext *gamesContext() const;
};

#endif // PSSTORAGE_H
