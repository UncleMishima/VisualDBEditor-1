#include "DBHandler.h"
#include "AbstractDB.h"
#include "Table.h"

DBHandler::DBHandler()
{
}

void DBHandler::openConnection(DBType type, QStringList options, uint flags)
{
    freeResources();

    db = AbstractDB::openConnection(type, options, flags);
    emit connectionSuccess();
}

void DBHandler::fillTables()
{
    Q_ASSERT_X(db != nullptr, "fillTables", "db = nullptr");

    tie<QVector<Table*>*&, AccessMode&>(tables, accessMod) = db->fillTables();
    emit fillTablesSuccess();
}

void DBHandler::setAccessMod(AccessMode am)
{
    accessMod = am;
}

AccessMode DBHandler::getAccessMod()
{
    return accessMod;
}

int DBHandler::getTablesCount()
{
    Q_ASSERT_X(tables != nullptr, "getTablesCount", "tables = nullptr");

    return tables->size();
}

QString DBHandler::getTableName(uint tableID)
{
    Q_ASSERT_X(tables != nullptr, "getTableName", "tables = nullptr");

    return tables->at(tableID)->getName();
}

QRect DBHandler::getTableGeometry(uint tableID, DisplayMode mode)
{
    Q_ASSERT_X(tables != nullptr, "getTableGeometry", "tables = nullptr");

    return tables->at(tableID)->getGeometry(mode);
}

QAbstractItemModel *DBHandler::getTableFieldsModel(uint tableID)
{
    Q_ASSERT_X(tables != nullptr, "getTablefieldsModel", "tables = nullptr");

    return tables->at(tableID)->getFieldsModel();
}

QAbstractItemModel *DBHandler::getTableObjectsModel(uint tableID)
{
    Q_ASSERT_X(tables != nullptr, "getTableObjectsModel", "tables = nullptr");

    return tables->at(tableID)->getObjectsModel();
}

void DBHandler::setTableName(uint tableID, const QString &tableName)
{
    Q_ASSERT_X(tables != nullptr, "setTableName", "tables = nullptr");

    tables->at(tableID)->setName(tableName);
}

void DBHandler::setTableX(uint tableID, int x, DisplayMode mode)
{
    Q_ASSERT_X(tables != nullptr, "setTableX", "tables = nullptr");

    tables->at(tableID)->setCoordX(x, mode);
}

void DBHandler::setTableY(uint tableID, int y, DisplayMode mode)
{
    Q_ASSERT_X(tables != nullptr, "setTableY", "tables = nullptr");

    tables->at(tableID)->setCoordY(y, mode);
}

void DBHandler::setTableHeight(uint tableID, int h, DisplayMode mode)
{
    Q_ASSERT_X(tables != nullptr, "setTableHeight", "tables = nullptr");

    tables->at(tableID)->setHeight(h, mode);
}


void DBHandler::setTableWidth(uint tableID, int w, DisplayMode mode)
{
    Q_ASSERT_X(tables != nullptr, "setTableWidth", "tables = nullptr");

    tables->at(tableID)->setWidth(w, mode);
}

void DBHandler::save()
{
    Q_ASSERT_X(db != nullptr, "save", "db = nullptr");
    Q_ASSERT_X(tables != nullptr, "save", "tables = nullptr");

    db->save(tables);

}

void DBHandler::freeResources()
{
    if (db != nullptr)
        delete db;

    if (tables == nullptr)
        return;

    foreach (Table *t, *tables)
        delete t;

    delete tables;
    tables = nullptr;
}
