#ifndef ABSTRACTDB_H
#define ABSTRACTDB_H

#include "GlobalDefinitions.h"

class Table;

class AbstractDB
{
protected:
    AbstractDB();

public:
    virtual ~AbstractDB(){}

    static AbstractDB *openConnection(DBType type,
                                      QStringList options,
                                      uint);
    virtual tuple<QVector<Table *>*, AccessMode> fillTables() = 0;

    virtual void save(QVector<Table* > *tables) = 0;

};

#endif // ABSTRACTDB_H
