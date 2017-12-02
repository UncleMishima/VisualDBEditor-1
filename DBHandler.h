#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <tuple>
#include <QVector>

#include "AbstractDB.h"
#include "GlobalDefinitions.h"
#include "XmlDB.h"

class DBHandler : public QObject
{
    Q_OBJECT
public:
    DBHandler();
    ~DBHandler() {freeResources();}

    AccessMod getAccessMod();
    int getTablesCount();
    QString getTableName(uint tableID);
    QRect getTableGeometry(uint tableID, DisplayMode mode);
    QAbstractItemModel *getTableFieldsModel(uint tableID);
    QAbstractItemModel *getTableObjectsModel(uint tableID);

    void setAccessMod(AccessMod am);
    void setTableName(uint tableID, const QString &tableName);
    void setTableX(uint tableID, int x, DisplayMode mode);
    void setTableY(uint tableID, int y, DisplayMode mode);
    void setTableWidth(uint tableID, int w, DisplayMode mode);
    void setTableHeight(uint tableID, int h, DisplayMode mode);

signals:
    void connectionSuccess();
    void connectionFailed(QString errorMsg);
    void fillTablesSuccess();
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
    void fillTables();
    void save();
    void freeUnusedMemmory();

private:
    AbstractDB* db = nullptr;
    QVector<Table*> *tables = nullptr;
    AccessMod accessMod;

    void freeResources();
};

#endif // DBHANDLER_H
