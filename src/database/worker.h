#ifndef WORKER_H
#define WORKER_H

#include "employee.h"

class Worker : public Employee
{
    LB_ROW(Worker);
public:
    Worker();
    Worker(const QString &name);

private:
    void initializeAttributes();
};

#endif // WORKER_H
