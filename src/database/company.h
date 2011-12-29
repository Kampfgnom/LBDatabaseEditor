#ifndef COMPANY_H
#define COMPANY_H

#include <LBDatabase/LBDatabase.h>

class Company : public LBDatabase::Row
{
    Q_OBJECT
    LB_ROW(Company);
public:
    QString name() const;
};

class Companies : public LBDatabase::Table
{
    Q_OBJECT
    LB_TABLE(Companies)
};

#endif // COMPANY_H
