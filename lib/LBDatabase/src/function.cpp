#include "function.h"

#include "storage.h"
#include "table.h"

namespace LBDatabase {

/******************************************************************************
** FunctionPrivate
*/
class FunctionPrivate {
    FunctionPrivate() :
        relationTable(0)
    {}

    void init();

    Row *row;
    Storage *storage;

    QString name;

    Table *relationTable;

    Function * q_ptr;
    Q_DECLARE_PUBLIC(Function)
};

void FunctionPrivate::init()
{
}

/******************************************************************************
** Function
*/
Function::Function(Row *row, Storage *parent) :
    Property(parent),
    d_ptr(new FunctionPrivate)
{
    Q_D(Function);
    d->q_ptr = this;
    d->row = row;
    d->storage = parent;
    d->init();
}

Function::~Function()
{
}


} // namespace LBDatabase
