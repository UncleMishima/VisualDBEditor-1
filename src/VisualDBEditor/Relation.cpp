#include "Relation.h"

void Relation::setTableId(uint index, uint id)
{
    Q_ASSERT_X(index < 2, "setTableId", "index out of range");
    tablesId[index] =  id;
}

void Relation::setTableFieldNumber(uint index, uint number)
{
    Q_ASSERT_X(index < 2, "setTableFieldNumber", "index out of range");
    tablesFieldNumbers[index] = number;
}

uint Relation::getTableId(uint index)
{
    Q_ASSERT_X(index < 2, "getTableId", "index out of range");
    return tablesId[index];
}

uint Relation::getTableFieldNumber(uint index)
{
    Q_ASSERT_X(index < 2, "getTableFieldNumber", "index out of range");
    return tablesFieldNumbers[index];
}
