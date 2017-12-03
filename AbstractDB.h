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
                                      uint flags);
    virtual QVector<Table *>* fillTables() = 0;

    //virtual void save();

};

#endif // ABSTRACTDB_H
