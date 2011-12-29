#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"

class Manager : public Employee
{
    LB_ROW(Manager);
public:
    Manager();
    Manager(const QString &name);

private:
    void initializeAttributes();

    LBDatabase::DatabaseAttribute* m_position;
};

#endif // MANAGER_H
