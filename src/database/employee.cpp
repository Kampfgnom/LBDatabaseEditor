#include "employee.h"

/*
  ##### Table Employees #####
  */
REGISTER_TABLE(Employee)

/*
  ##### Row Employee ####
  */
REGISTER_ROW(Employee,
         INHERITS LBDatabase::Row,
         BASECLASS Employee);

Employee::Employee() :
    Row(Employees::instance())
{
}

Employee::Employee(const QString &name, int salary) :
    Row(Employees::instance())
{
    m_name->setValue(name);
    m_salary->setValue(salary);
}

void Employee::initializeAttributes()
{
    m_name = new LBDatabase::DatabaseAttribute("name", "Name", this);
    m_salary = new LBDatabase::DatabaseAttribute("salary", "Salary", this);
}
