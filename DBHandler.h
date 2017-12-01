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

private:
    AbstractDB* db;
    QVector<Table*>* tables;
    AccessMod accessMod;

    QVector< std::tuple<QString, QRect, QAbstractItemModel*> >* tablesData;

    void save();
    void freeUnusedMemmory();

};

#endif // DBHANDLER_H
