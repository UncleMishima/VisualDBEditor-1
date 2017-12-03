#include "Controller.h"
#include "MainWindow.h"
#include "DBHandler.h"

Controller::Controller()
{

    // debug For now this is it, later we will create it in another thread
    dbHandler = new DBHandler;

    mainWindow = new MainWindow(dbHandler);

    connect(this, SIGNAL(openConnection(DBType,QStringList,uint)),
            dbHandler, SLOT(openConnection(DBType,QStringList,uint)));

    connect(this, SIGNAL(fillTables()),
            dbHandler, SLOT(fillTables()));

    connect(dbHandler, SIGNAL(fillTablesSuccess()),
            this, SLOT(fillTablesSuccess()));

    connect(dbHandler, SIGNAL(connectionSuccess()),
            this, SLOT(connectionSuccess()));

}

Controller::~Controller()
{
}

void Controller::start()
{
    mainWindow->showMaximized();

    QStringList options(QString("test.xml"));
    emit openConnection(XML_FILE, options, STRUCTURE_EDIT);
}

void Controller::connectionSuccess()
{
    emit fillTables();
}

void Controller::fillTablesSuccess()
{
    // debug For now this is it, later acces mode will be obtained before this call
    mainWindow->showTables(AccessMode::STRUCTURE_EDIT, DisplayMode::OBJECTS);
}

