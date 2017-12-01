#include "DBHandler.h"

DBHandler::DBHandler()
{

}

void DBHandler::openConnection(DBType t, QString url, QString dbName, QString userName, QString password, ConnectionFlags f)
{
    if(t == XML_FILE)
    {
        db = new XmlDB(url);
    }
    else qDebug() << "Error: openConnection() : DBHandler";

    emit connectionSuccess();
}

void DBHandler::fillTables(DisplayMode m, QVector<Table *> *tables)
{
    QVector<Table *> *t = db->fillTables(m, tables);
    emit fillTablesSuccess(t);
}

void DBHandler::setTables(QVector<Table*>* tbs)
{
    tables = tbs;
}

QVector<Table*>* DBHandler::getTables()
{
    return tables;
}


void DBHandler::setAccessMod(AccessMod am)
{
    accessMod = am;
}

AccessMod DBHandler::getAccessMod()
{
    return accessMod;
}

QVector< std::tuple<QString, QRect, QAbstractItemModel*> >* DBHandler::getTablesData()
{
    return tablesData;
}

void DBHandler::setTableName(uint tableID, QString tableName, DisplayMode mode)
{
    tables->at(tableID)->setName(tableName);
}

void DBHandler::setTableX(uint tableID, int x, DisplayMode mode)
{
    tables->at(tableID)->setCoordX(x);
}


void DBHandler::setTableY(uint tableID, int y, DisplayMode mode)
{
    tables->at(tableID)->setCoordY(y);
}

void DBHandler::setTableH(uint tableID, int h, DisplayMode mode)
{
    tables->at(tableID)->setCoordX(h);
}


void DBHandler::setTableW(uint tableID, int w, DisplayMode mode)
{
    tables->at(tableID)->setCoordY(w);
}



void DBHandler::save()
{

}

void DBHandler::freeUnusedMemmory()
{

}


