#include "Controller.h"

#include <QDebug>
#include <QQmlContext>

// debug
DBHandler dbHandler;

Controller::Controller(QObject *parent): QObject(parent)
{
    quickWidget.rootContext()->setContextProperty("controller", this);
    quickWidget.rootContext()->setContextProperty("quickWidget", &quickWidget);
    qmlRegisterType<QTableViewWrapper>("QTableViewWrapper", 1, 0,
                                       "QTableViewWrapper");


    quickWidget.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    quickWidget.setResizeMode(QQuickWidget::SizeRootObjectToView);

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
    freeResources();
}

void Controller::start()
{
    quickWidget.show();

    //debug
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
    QQmlComponent component(quickWidget.engine(), QUrl(QStringLiteral("qrc:/TableFrame.qml")));
    QObject *tableFrame = component.create();
    QQuickItem *item = qobject_cast<QQuickItem*>(tableFrame);

    QQuickItem *root = quickWidget.rootObject();

    item->setParentItem(root);
    item->setX(table->getCoordX());
    item->setY(table->getCoordY());
    item->setWidth(table->getWidth());
    item->setHeight(table->getHeight());

    tableFrame->setProperty("headerText", table->getName());
    //tableFrame->setProperty("model", table->getRowsModel());
    //tableFrame->setProperty("parentWidget", quickWidget);

    QTableView *tableView = tableFrame->property("tableView").value<QTableView*>();
    tableView->setParent(&quickWidget);
    tableView->setModel(table->getRowsModel());
    tableView->show();

    tableFrames.push_back(tableFrame);
}

void Controller::freeResources()
{
    if (tableViews != nullptr)
    {
        foreach (QTableView *view, *tableViews)
            delete view;
    }

    foreach (QObject *frame, tableFrames)
        delete frame;
}

