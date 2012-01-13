#ifndef LBDATABASE_FUNCTION_H
#define LBDATABASE_FUNCTION_H

#include "property.h"

namespace LBDatabase {

class Row;
class Storage;

class FunctionPrivate;
class Function : public Property
{
public:
    ~Function();

private:
    explicit Function(Row *row, Storage *parent);

    QScopedPointer<FunctionPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Function)
    Q_DISABLE_COPY(Function)
};

} // namespace LBDatabase

#endif // LBDATABASE_FUNCTION_H
