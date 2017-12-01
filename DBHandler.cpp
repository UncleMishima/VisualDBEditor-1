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

void DBHandler::save()
{

}
