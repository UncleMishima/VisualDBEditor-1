#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "GlobalDefinitions.h"
#include "DBHandler.h"

class Controller: QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void start();
    Q_INVOKABLE void createTableFrame(Table *table);

signals:
    void openConnection(DBType tm, QString url, QString dbName,
                        QString userName, QString password, ConnectionFlags f);
    void fillTables(DisplayMode m, QVector<Table*>* tables);

public slots:
    void connectionSuccess();
    void fillTablesSuccess(QVector<Table*>* tables);

private:
};

#endif // CONTROLLER_H
