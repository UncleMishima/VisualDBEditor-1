#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>

#include "DBHandler.h"
#include "TableView.h"

// debug
#include "Table.h"

MainWindow::MainWindow(DBHandler *h):
    ui(new Ui::MainWindow),
    dbHandler(h),
    tableViews(nullptr),
    tablesScene(new QWidget),
    scrollArea(new QScrollArea)
{
    ui->setupUi(this);

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
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Open file..."),
                                QDir::currentPath(),
                                "XML file(*.xml)");
}

void MainWindow::slot_fileSave()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save Xml", ".", "Xml files (*.xml)");
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

void MainWindow::showTables(AccessMod accesMod, DisplayMode displayMod)
{
    freeResources();
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

void MainWindow::tableXChanged(uint tableId, int x)
{
    tablesScene->adjustSize();
}

void MainWindow::tableYChanged(uint tableId, int y)
{

    tablesScene->adjustSize();
}

void MainWindow::tableWidthChanged(uint tableId, int wtableIdth)
{
    tablesScene->adjustSize();

}

void MainWindow::tableHeightChanged(uint tableId, int height)
{
    tablesScene->adjustSize();
}

void MainWindow::tableNameChanged(uint tableId, QString name)
{
    tablesScene->adjustSize();
}

// debug
void MainWindow::createTableView(Table *table)
{
    TableView *tv = new TableView(tablesScene);

    tv->setTableName(table->getName());
    tv->setGeometry(table->getCoordX(), table->getCoordY(),
                    table->getWidth(), table->getHeight());
    tv->setModel(table->getRowsModel());
    tv->setAccesMod(STRUCTURE_EDIT);
    tv->show();

    // debug
    tablesScene->adjustSize();

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

    if (tableViews == nullptr)
        tableViews = new QVector<TableView*>;

    tableViews->push_back(tv);
}
