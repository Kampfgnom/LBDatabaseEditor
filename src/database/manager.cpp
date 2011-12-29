#include "manager.h"

/*
  ##### Row Manager ####
  */
REGISTER_ROW(Manager,
         INHERITS Employee,
         BASECLASS Employee);

Manager::Manager() :
    Employee()
{
}

Manager::Manager(const QString &name) :
    Employee(name, 100000)
{
}

void Manager::initializeAttributes()
{
    m_position = new LBDatabase::DatabaseAttribute("position", "Position", this);
}
