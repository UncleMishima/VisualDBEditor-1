#ifndef ABSTRACTDB_H
#define ABSTRACTDB_H

#include <QVector>

#include "GlobalDefinitions.h"
#include "Table.h"

class AbstractDB
{
public:
    AbstractDB();

    virtual QVector<Table *>* fillTables() = 0;

};

#endif // ABSTRACTDB_H
