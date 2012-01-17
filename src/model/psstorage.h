#ifndef PSSTORAGE_H
#define PSSTORAGE_H

#include <LBDatabase/LBDatabase.h>

class GamesContext;

class PSStorage : public LBDatabase::Storage
{
public:
    PSStorage(const QString &fileName, QObject *parent = 0);

    GamesContext *gamesContext() const;
};

#endif // PSSTORAGE_H
