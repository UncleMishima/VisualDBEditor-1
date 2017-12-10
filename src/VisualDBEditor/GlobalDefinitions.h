#ifndef GLOBALDEFINITIONS_H
#define GLOBALDEFINITIONS_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QRect>
#include <QAbstractItemModel>
#include <tuple>

using std::tuple;
using std::tie;

enum DBType
{
    XML_FILE,
    POSTGRES_DB
};

Q_DECLARE_METATYPE(DBType)

enum XmlFlag
{
    NO_FLAG,
    READ,
    WRITE
};

enum DisplayMode
{
    CLASSES = 0,
    FIELDS = 1,
    OBJECTS = 2
};

enum AccessMode
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
