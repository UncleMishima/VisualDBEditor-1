#ifndef ABSTRACTDB_H
#define ABSTRACTDB_H

#include <QVector>

#include "table.h"

class AbstractDB
{
public:
    AbstractDB();

    virtual void fillTables(QVector<Table *> *tables) = 0;

};

#endif // ABSTRACTDB_H
