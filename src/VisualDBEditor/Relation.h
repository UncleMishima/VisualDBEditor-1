#ifndef RELATION_H
#define RELATION_H

#include "GlobalDefinitions.h"

class Relation
{
public:
    Relation();

    void setFirstTableId(uint id) {firstTableId = id;}
    void setFirstTableFieldNumber(uint number) {firstTableFieldNumber = number;}
    void setSecondTableId(uint id) {secondTableId = id;}
    void setSecondTableFieldNumber(uint number) {secondTableFieldNumber = number;}

    uint getFirstTableId() {return firstTableId;}
    uint getFirstTableFieldNumber() {return firstTableFieldNumber;}
    uint getSecondTableId() {return secondTableId;}
    uint getSecondTableFieldNumber() {return secondTableFieldNumber;}

private:
    uint firstTableId;
    uint firstTableFieldNumber;
    uint secondTableId;
    uint secondTableFieldNumber;
};

#endif // RELATION_H
