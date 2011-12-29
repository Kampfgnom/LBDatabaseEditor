#include "company.h"

LB_REGISTER_TABLE(Companies)
LB_REGISTER_ROW(Company,
                INHERITS LBDatabase::Row)

QString Company::name() const
{
    return attribute(QLatin1String("name"))->data().toString();
}
