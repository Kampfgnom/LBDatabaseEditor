#ifndef PSSTORAGE_H
#define PSSTORAGE_H

#include <LBDatabase/LBDatabase.h>

class PSStorage : public LBDatabase::Storage
{
public:
    PSStorage(const QString &fileName, QObject *parent = 0);
};

#endif // PSSTORAGE_H
