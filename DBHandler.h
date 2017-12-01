#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <tuple>
#include "AbstractDB.h"
#include "GlobalDefinitions.h"
#include "XmlDB.h"

class DBHandler : public QObject
{
    Q_OBJECT
public:
    DBHandler();

    void setTables(QVector<Table*>*);
    QVector<Table*>* getTables();

    void setAccessMod(AccessMod am);
    AccessMod getAccessMod();

    QVector< std::tuple<QString, QRect, QAbstractItemModel*> >* getTablesData();

    void setTableName(uint tableID, QString tableName, DisplayMode mode);
    void setTableX(uint tableID, int x, DisplayMode mode);
    void setTableY(uint tableID, int y, DisplayMode mode);
    void setTableW(uint tableID, int w, DisplayMode mode);
    void setTableH(uint tableID, int h, DisplayMode mode);

signals:
    void connectionSuccess();
    void connectionFailed(QString errorMsg);
    void fillTablesSuccess(QVector<Table*>* tables);
    void fillTablesFailed(QString errorMsg);
    void saveSuccess();
    void saveFailed(QString errorMsg);

public slots:
    void openConnection(
            DBType t,
            QString url,
            QString dbName,
            QString userName,
            QString password,
            ConnectionFlags f
            );

    void fillTables(DisplayMode m, QVector<Table *> *tables);

private:
    AbstractDB* db;
    QVector<Table*>* tables;
    AccessMod accessMod;

    QVector< std::tuple<QString, QRect, QAbstractItemModel*> >* tablesData;

    void save();
    void freeUnusedMemmory();

};

#endif // DBHANDLER_H
