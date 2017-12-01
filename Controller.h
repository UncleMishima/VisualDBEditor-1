#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "GlobalDefinitions.h"

class DBHandler;
class MainWindow;

class Controller: public QObject
{
    Q_OBJECT
public:
    explicit Controller();
    ~Controller();
    void start();

signals:
    void openConnection(DBType tm, QString url, QString dbName,
                        QString userName, QString password, ConnectionFlags f);
    void fillTables();

public slots:
    void connectionSuccess();
    void fillTablesSuccess();

private:
    DBHandler *dbHandler;
    MainWindow *mainWindow;
};

#endif // CONTROLLER_H
