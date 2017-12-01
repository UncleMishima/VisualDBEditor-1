#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <tuple>
#include <QVector>

#include "AbstractDB.h"
#include "GlobalDefinitions.h"
#include "XmlDB.h"

using std::tuple;

typedef QVector<tuple<QString, QRect, QAbstractItemModel*>> TablesDataVector;

class DBHandler : public QObject
{
    Q_OBJECT
public:
    DBHandler();

    TablesDataVector* getTablesData(DisplayMode mode);
    AccessMod getAccessMod();

    void setAccessMod(AccessMod am);
    void setTableName(uint tableID, QString tableName, DisplayMode mode);
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
    QVector<Table*>* tables = nullptr;
    AccessMod accessMod;
};

#endif // DBHANDLER_H
