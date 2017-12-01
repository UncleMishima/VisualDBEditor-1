#ifndef ABSTRACTDB_H
#define ABSTRACTDB_H

#include <QVector>

#include "GlobalDefinitions.h"
#include "Table.h"

class AbstractDB
{
public:
    AbstractDB();

    //virtual static AbstractDB* openConnection(DBType t, QStringList options, uint flags) = 0;
    virtual QVector<Table *>* fillTables() = 0;

    //virtual void save();

};

#endif // ABSTRACTDB_H
