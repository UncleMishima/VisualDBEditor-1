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

void DBHandler::fillTables()
{
    db->fillTables();
    emit fillTablesSuccess();
}

void DBHandler::setAccessMod(AccessMod am)
{
    accessMod = am;
}

AccessMod DBHandler::getAccessMod()
{
    return accessMod;
}

TablesDataVector* DBHandler::getTablesData(DisplayMode mode)
{
    return nullptr;
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

void DBHandler::setTableHeight(uint tableID, int h, DisplayMode mode)
{
    tables->at(tableID)->setCoordX(h);
}


void DBHandler::setTableWidth(uint tableID, int w, DisplayMode mode)
{
    tables->at(tableID)->setCoordY(w);
}



void DBHandler::save()
{

}

void DBHandler::freeUnusedMemmory()
{

}


