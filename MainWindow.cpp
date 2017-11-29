#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>

#include "DBHandler.h"
#include "TableView.h"

MainWindow::MainWindow(DBHandler *h, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbHandler(h),
    tableViews(nullptr)
{
    ui->setupUi(this);
    createMenu();
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

void MainWindow::xChanged(uint tableId, int x)
{

}

void MainWindow::yChanged(uint tableId, int y)
{

}

void MainWindow::widthChanged(uint tableId, int wtableIdth)
{

}

void MainWindow::heightChanged(uint tableId, int height)
{
}

void MainWindow::tableNameChanged(uint tableId, QString name)
{
}
