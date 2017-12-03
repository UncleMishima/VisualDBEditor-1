#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QFile>

#include "DBHandler.h"
#include "TableView.h"

MainWindow::MainWindow(DBHandler *h):
    ui(new Ui::MainWindow),
    dbHandler(h),
    tableViews(nullptr),
    tablesScene(new QWidget),
    scrollArea(new QScrollArea)
{
    ui->setupUi(this);

    setWindowTitle(QString("VisualDBEditor"));

    createMenu();

    scrollArea->setWidget(tablesScene);
    setCentralWidget(scrollArea);
}

MainWindow::~MainWindow()
{
    freeResources();

    delete ui;
}

void MainWindow::slot_fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
                                this,
                                QString::fromUtf8("Open file..."),
                                QDir::currentPath(),
                                "XML file(*.xml)");
}

void MainWindow::slot_fileSave()
{
    QString filePath = QFileDialog::getSaveFileName(
                                    this, "Save Xml", ".", "Xml files (*.xml)");
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    fileOpen = new QAction(tr("&Open"), this);
    connect(fileOpen, SIGNAL(triggered()), this, SLOT(slot_fileOpen()));
    fileMenu->addAction(fileOpen);

    fileSave = new QAction(tr("&Save"), this);
    connect(fileSave, SIGNAL(triggered()), this, SLOT(slot_fileSave()));
    fileMenu->addAction(fileSave);

    fileMenu->addSeparator();

    fileExit = new QAction(tr("&Exit"), this);
    connect(fileExit, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu->addAction(fileExit);
}

void MainWindow::showTables(AccessMode accesMod, DisplayMode displayMode)
{
    freeResources();

    this->displayMode = displayMode;

    int tablesCount = dbHandler->getTablesCount();
    tableViews = new QVector<TableView*>(tablesCount);

    for (int i = 0; i < tablesCount; i++)
    {
        TableView *tv = new TableView(tablesScene);

        tv->setID(i);
        tv->setTableName(dbHandler->getTableName(i));
        tv->setGeometry(dbHandler->getTableGeometry(i, displayMode));

        switch (displayMode)
        {
            case CLASSES:
                tv->setModel(nullptr);
                break;

            case FIELDS:
                tv->setModel(dbHandler->getTableFieldsModel(i));
                break;

            case OBJECTS:
                tv->setModel(dbHandler->getTableObjectsModel(i));
                break;
        }

        tv->setAccesMod(accesMod);
        tv->show();

        connect(tv, SIGNAL(xChanged(uint,int)),
                this, SLOT(tableXChanged(uint,int)));

        connect(tv, SIGNAL(yChanged(uint,int)),
                this, SLOT(tableYChanged(uint,int)));

        connect(tv, SIGNAL(widthChanged(uint,int)),
                this, SLOT(tableWidthChanged(uint,int)));

        connect(tv, SIGNAL(heightChanged(uint,int)),
                this, SLOT(tableHeightChanged(uint,int)));

        connect(tv, SIGNAL(tableNameChanged(uint,QString)),
                this, SLOT(tableNameChanged(uint,QString)));

        (*tableViews)[i] = tv;
    }

   tablesScene->adjustSize();
}

void MainWindow::freeResources()
{
    if (tableViews == nullptr)
        return;

    foreach (TableView *view, *tableViews)
        delete view;

    delete tableViews;
    tableViews = nullptr;
}

void MainWindow::tableXChanged(uint tableID, int x)
{
    tablesScene->adjustSize();

    dbHandler->setTableX(tableID, x, displayMode);
}

void MainWindow::tableYChanged(uint tableID, int y)
{
    tablesScene->adjustSize();

    dbHandler->setTableY(tableID, y, displayMode);
}

void MainWindow::tableWidthChanged(uint tableID, int width)
{
    tablesScene->adjustSize();

    dbHandler->setTableWidth(tableID, width, displayMode);
}

void MainWindow::tableHeightChanged(uint tableID, int height)
{
    tablesScene->adjustSize();

    dbHandler->setTableHeight(tableID, height, displayMode);
}

void MainWindow::tableNameChanged(uint tableID, const QString &name)
{
    tablesScene->adjustSize();

    dbHandler->setTableName(tableID, name);
}
