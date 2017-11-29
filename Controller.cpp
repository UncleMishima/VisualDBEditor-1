#include "Controller.h"
#include "TableView.h"
#include "MainWindow.h"

#include <QDebug>

// debug
DBHandler dbHandler;
MainWindow *mainW;

Controller::Controller(QObject *parent): QObject(parent)
{
    // debug
    connect(this, SIGNAL(openConnection(DBType,QString,QString,
                                        QString,QString,ConnectionFlags)),
            &dbHandler, SLOT(openConnection(DBType,QString,QString,
                                            QString,QString,ConnectionFlags)));
    connect(this, SIGNAL(fillTables(DisplayMode,QVector<Table*>*)),
            &dbHandler, SLOT(fillTables(DisplayMode,QVector<Table*>*)));
    connect(&dbHandler, SIGNAL(fillTablesSuccess(QVector<Table*>*)),
            this, SLOT(fillTablesSuccess(QVector<Table*>*)));
    connect(&dbHandler, SIGNAL(connectionSuccess()),
            this, SLOT(connectionSuccess()));

}

Controller::~Controller()
{
}

void Controller::start()
{
    //debug
    mainW = new MainWindow(&dbHandler);

    mainW->showMaximized();

    emit openConnection(XML_FILE, "test.xml", "", "", "", CREATE);
}

void Controller::connectionSuccess()
{
    emit fillTables(OBJECTS, nullptr);
}

void Controller::fillTablesSuccess(QVector<Table*>* tables)
{
    //debug
    for (int i = 0; i < tables->size(); i++)
        createTableFrame(tables->at(i));
}

void Controller::createTableFrame(Table *table)
{
    TableView *tv = new TableView(mainW->centralWidget());

    tv->setTableName(table->getName());
    tv->setGeometry(table->getCoordX(), table->getCoordY(), table->getWidth(), table->getHeight());
    tv->setModel(table->getRowsModel());
    tv->setAccesMod(STRUCTURE_EDIT);

    tv->show();
}
