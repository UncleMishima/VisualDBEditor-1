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

    TablesDataVector* getTablesData(DisplayMode mod){}

signals:
    void connectionSuccess();
    void connectionFailed(QString errorMsg);
    void fillTablesSuccess();
    void fillTablesFailed(QString errorMsg);
    void saveSuccess();
    void daveFailed(QString errorMsg);

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

private:
    AbstractDB* db;

};

#endif // DBHANDLER_H
