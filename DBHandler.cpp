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
}

void DBHandler::fillTables(DisplayMode m, QVector<Table *> *tables)
{
    db->fillTables(m, tables);
    emit fillTablesSuccess(tables);
}

void DBHandler::save(QVector<Table *> *tables)
{

}
