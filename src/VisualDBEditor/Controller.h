#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

#include "GlobalDefinitions.h"
#include <QStandardItemModel>

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
    void createNewTable(QString tableName, QStandardItemModel* objectsModel, QStandardItemModel* fieldModel);
    void deleteClass(uint id);


signals:
    void openConnection(DBType type, QStringList options, uint flags);
    void fillTables();
    void save();
    void createTable(QString tableName, QStandardItemModel* objectsModel, QStandardItemModel* fieldModel);
    void deleteClassS(uint id);

public slots:
    void connectionSuccess();
    void fillTablesSuccess();

private:
    DBHandler *dbHandler;
    MainWindow *mainWindow;
    QThread dbHandlerThread;
};

#endif // CONTROLLER_H
