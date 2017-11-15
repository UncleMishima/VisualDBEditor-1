#ifndef GLOBALDEFINITIONS_H
#define GLOBALDEFINITIONS_H

#include <QObject>
#include <QVector>
#include <QTableView>
#include <QQuickView>
#include <QString>
#include <QStandardItemModel>

enum DBType
{
    XML_FILE,
    POSTGRES_DB
};


enum DisplayMode
{
    CLASSES,
    FIELDS,
    OBJECTS
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
