#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <LBDatabase/LBDatabase.h>

class Employee : public LBDatabase::Row
{
    LB_ROW(Employee);
public:
    Employee();
    Employee(const QString &name, int salary);

private:
    void initializeAttributes();

    LBDatabase::DatabaseAttribute* m_name;
    LBDatabase::DatabaseAttribute* m_salary;
};

class Employees : public LBDatabase::Table<Employee>
{
    LB_TABLE(Employee);
};

#endif // EMPLOYEE_H
