#ifndef DBHANDLER_H
#define DBHANDLER_H

#include "AbstractDB.h"
#include "GlobalDefinitions.h"
#include "XmlDB.h"

class DBHandler : public QObject
{
    Q_OBJECT
public:
    DBHandler();

signals:
    void connectionSuccess();
    void connectionFailed(QString errorMsg);
    void fillTablesSuccess(QVector<Table*>* tables);
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

    void fillTables(DisplayMode m, QVector<Table *> *tables);
    void save(QVector<Table*>* tables);

private:
    AbstractDB* db;

};

#endif // DBHANDLER_H
