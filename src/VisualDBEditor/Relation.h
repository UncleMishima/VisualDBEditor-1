#ifndef RELATION_H
#define RELATION_H

#include "GlobalDefinitions.h"

class Relation
{
public:
    void setTableId(uint index, uint id);
    void setTableFieldNumber(uint index, uint number);

    uint getTableId(uint index);
    uint getTableFieldNumber(uint index);

    uint tablesId[2];
    uint tablesFieldNumbers[2];
};

#endif // RELATION_H
