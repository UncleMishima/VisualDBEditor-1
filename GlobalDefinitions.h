#ifndef GLOBALDEFINITIONS_H
#define GLOBALDEFINITIONS_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QRect>
#include <QAbstractItemModel>

enum DBType
{
    XML_FILE,
    POSTGRES_DB
};


enum DisplayMode
{
    CLASSES = 0,
    FIELDS = 1,
    OBJECTS = 2
};

enum AccessMod
{
    VIEW_ONLY,
    DATA_EDIT,
    STRUCTURE_EDIT
};

enum ConnectionFlags
{
    CREATE
};


#endif // GLOBALDEFINITIONS_H
