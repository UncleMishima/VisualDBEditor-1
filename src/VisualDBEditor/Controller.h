#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

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
    void saveTables();

signals:
    void openConnection(DBType type, QStringList options, uint flags);
    void fillTables();
    void save();

public slots:
    void connectionSuccess();
    void fillTablesSuccess();

private:
    DBHandler *dbHandler;
    MainWindow *mainWindow;
    QThread dbHandlerThread;
};

#endif // CONTROLLER_H
