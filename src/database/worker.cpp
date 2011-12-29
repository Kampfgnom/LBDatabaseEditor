#include "worker.h"

/*
  ##### Row Worker ####
  */
REGISTER_ROW(Worker,
         INHERITS Employee,
         BASECLASS Employee);

Worker::Worker() :
    Employee()
{
}

Worker::Worker(const QString &name) :
    Employee(name, 30000)
{
}


void Worker::initializeAttributes()
{
}
