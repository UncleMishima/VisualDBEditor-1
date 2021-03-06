#include "Controller.h"
#include "MainWindow.h"
#include "DBHandler.h"

Controller::Controller()
{
    dbHandler = new DBHandler;
    dbHandler->moveToThread(&dbHandlerThread);

    mainWindow = new MainWindow(dbHandler, this);

    qRegisterMetaType<DBType>();

    connect(&dbHandlerThread, SIGNAL(finished()),
             dbHandler, SLOT(deleteLater()));

    connect(this, SIGNAL(save()), dbHandler, SLOT(save()));

    connect(this, SIGNAL(openConnection(DBType,QStringList,uint)),
            dbHandler, SLOT(openConnection(DBType,QStringList,uint)));

    connect(this, SIGNAL(fillTables()),
            dbHandler, SLOT(fillTables()));

    connect(dbHandler, SIGNAL(fillTablesSuccess()),
            this, SLOT(fillTablesSuccess()));

    connect(dbHandler, SIGNAL(connectionSuccess()),
            this, SLOT(connectionSuccess()));

    connect(this, SIGNAL(createTable(QString,QStandardItemModel*,QStandardItemModel*)),
            dbHandler, SLOT(createTable(QString,QStandardItemModel*,QStandardItemModel*)), Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(deleteClassSignal(uint)),
            dbHandler, SLOT(deleteClass(uint)));

    dbHandlerThread.start();
}

Controller::~Controller()
{
    delete mainWindow;

    dbHandlerThread.quit();
    dbHandlerThread.wait();
}


void Controller::createNewTable(QString tableName, QStandardItemModel* objectsModel, QStandardItemModel* fieldModel)
{
    emit createTable(tableName, objectsModel, fieldModel);
}

void Controller::deleteClass(uint id)
{
    emit deleteClassSignal(id);
}


void Controller::start()
{
    mainWindow->showMaximized();

    QStringList options(QString("test.xml"));
    emit openConnection(XML_FILE, options, STRUCTURE_EDIT);
}

void Controller::saveTables()
{
    emit save();
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

