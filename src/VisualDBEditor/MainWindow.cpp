#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ui_addclass.h"

#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QLineEdit>
#include <QToolBar>
#include <QDebug>
#include <QMouseEvent>
#include <QStandardItemModel>

#include "DBHandler.h"
#include "TableView.h"
#include "Controller.h"
#include "TablesDrawingArea.h"
#include "Relation.h"
#include "AddClass.h"
#include "RelationsManager.h"

MainWindow::MainWindow(DBHandler *h, Controller *c):
    ui(new Ui::MainWindow),
    dbHandler(h),
    controller(c),
    isRelationsEditingModeActivated(false),
    tablesDrawingArea(new TablesDrawingArea),
    scrollArea(new QScrollArea)
{
    ui->setupUi(this);

    setWindowTitle(QString("VisualDBEditor"));

    createMenu();
    createToolBar();
    
    zoomCounter = 0;
    zoomFactor = 30;
    mwCenterXCoord = this->width()/2;
    mwCenterYCoord = this->height()/2;

    scrollArea->setWidget(tablesDrawingArea);
    setCentralWidget(scrollArea);

    relationsManager = new RelationsManager(this);
}

MainWindow::~MainWindow()
{
    freeResources();

    delete relationsManager;
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

void MainWindow::slot_fileSaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(
                                    this, "Save Xml", ".", "Xml files (*.xml)");
}


void MainWindow::slot_fileSave()
{
    controller->saveTables();
}

/*
void MainWindow::slot_chooseFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this, QString::fromUtf8("Choose the font"));
    if (ok)
    {
        for(int i = 0; i < tableViews.size(); i++)
        {
            tableViews.at(i)->setFont(font);
        }
    }
    else
    {
        //if user pushed "Cancel" activated default font(Times, 12pt)
    }
}
*/

void MainWindow::slot_addClasses()
{
    newClass = new AddClass();
    newClass->show();

    if(newClass->exec() == QDialog::Accepted)
    {
        addNewClass();
    }
    else if(newClass->exec() == QDialog::Rejected)
    {
        qDebug() << "Table has not created";
    }
}

void MainWindow::slot_zoomIn()
{
    if(zoomCounter <= zoomFactor)
    {
        for(int i = 0; i < tableViews.size(); ++i)
        {
            double newXCoord = tableViews.at(i)->x() + (mwCenterXCoord - tableViews.at(i)->x())/tableViews.at(i)->getDragStep();
            double newYCoord = tableViews.at(i)->y() + (mwCenterYCoord - tableViews.at(i)->y())/tableViews.at(i)->getDragStep();
            tableViews.at(i)->setCoords(tableViews.at(i)->getID(), newXCoord, newYCoord);
            //++zoomCounter;
        }
    }
    else return;

    applyToAll();
}

void MainWindow::slot_zoomOut()
{
    if(zoomCounter >= -zoomFactor)
    {
        for(int i = 0; i < tableViews.size(); ++i)
        {
            double newXCoord = tableViews.at(i)->x() - (mwCenterXCoord - tableViews.at(i)->x())/tableViews.at(i)->getDragStep();
            double newYCoord = tableViews.at(i)->y() - (mwCenterYCoord - tableViews.at(i)->y())/tableViews.at(i)->getDragStep();
            tableViews.at(i)->setCoords(tableViews.at(i)->getID(), newXCoord, newYCoord);
            //--zoomCounter;
        }
    }
    else return;

    applyToAll();
}

void MainWindow::moveTables(int zoomF)
{
    double mwCenterXCoord = this->geometry().width()/2;
    double mwCenterYCoord = this->geometry().height()/2;

    for(int i = 0; i < tableViews.size(); ++i)
    {
        double newXCoord = tableViews.at(i)->x() + (mwCenterXCoord - tableViews.at(i)->x())/zoomFactor;
        double newYCoord = tableViews.at(i)->y() + (mwCenterYCoord - tableViews.at(i)->y())/zoomFactor;
        tableViews.at(i)->setCoords(tableViews.at(i)->getID(), newXCoord, newYCoord);
    }
}

void MainWindow::addNewClass()
{
    QStandardItemModel* objectsModel = new QStandardItemModel();
    QStandardItemModel* fieldsModel = new QStandardItemModel();

    for(uint j = 0; j < newClass->ITEM_COUNT; j++)
    {
        if(newClass->ui->fieldsTableWidget->item(0, j) == nullptr || newClass->ui->fieldsTableWidget->item(1, j) == nullptr)
        {
            continue;
        }
        else
        {
            fieldsModel->setItem(j, 0, new QStandardItem(newClass->ui->fieldsTableWidget->item(0, j)->text()));
            fieldsModel->setItem(j, 1, new QStandardItem(newClass->ui->fieldsTableWidget->item(1, j)->text()));
        }
    }

    for(uint i = 0; i < newClass->ITEM_COUNT; i++)
    {
        for(uint j = 0; j < newClass->ITEM_COUNT; j++)
        {
            if(newClass->ui->objectsTableWidget->item(i, j) == nullptr)
            {
                continue;
            }
            else
            {
                objectsModel->setItem(i, j, new QStandardItem(newClass->ui->objectsTableWidget->item(i, j)->text()));
            }
        }
    }

    QString tableName = newClass->ui->lineEdit->text();
    controller->createTable(tableName, objectsModel, fieldsModel);
    showTables(STRUCTURE_EDIT, displayMode);

    //QTableView* tv = new QTableView();
    //tv->setModel(objectsModel);
    //tv->setModel(fieldsModel);
    //tv->show();
}

void MainWindow::deleteClass(uint id)
{
    controller->deleteClass(id);

    for(int i = id + 1; i < tableViews.size(); i++)
    {
        tableViews.at(i)->setID(i-1);
    }

    tableViews.at(id)->deleteLater();
    tableViews.remove(id);
}

void MainWindow::switchRelationsEditingMode()
{
   isRelationsEditingModeActivated = !isRelationsEditingModeActivated;

   if (!isRelationsEditingModeActivated)
       clicksCount = 0;
}

void MainWindow::switchRelationsShowing()
{
    tablesDrawingArea->switchRelationsShowing();
    tablesDrawingArea->update();
}


void MainWindow::applyToAll()
{
    for (int i = 0; i < tableViews.size(); i++)
    {
        QPoint pos = tableViews.at(i)->pos();

        dbHandler->setTablePos(i, pos, CLASSES);
        dbHandler->setTablePos(i, pos, OBJECTS);
        dbHandler->setTablePos(i, pos, FIELDS);
    }
}

void MainWindow::createMenu()
{
    //font view menu
    //tableMenu = menuBar()->addMenu(tr("&Table"));
    //tableMenu->addAction(chooseFont);

    //font view action and connect
    //chooseFont = new QAction(tr("&Choose font"), this);
    //connect(chooseFont, SIGNAL(triggered()), this, SLOT(slot_chooseFont()));

    createFileMenu();
    createClassMenu();
    createViewMenu();
    createScaleMenu();

    //QMenu *classMenu = menuBar()->addMenu(tr("&Classes"));
}

void MainWindow::createFileMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *fileOpen, *fileExit, *fileSave, *fileSaveAs;

    fileOpen = new QAction(tr("&Open"), this);
    connect(fileOpen, SIGNAL(triggered()), this, SLOT(slot_fileOpen()));

    fileSave = new QAction(tr("&Save"), this);
    connect(fileSave, SIGNAL(triggered()), this, SLOT(slot_fileSave()));

    fileSaveAs = new QAction(tr("&Save As..."), this);
    connect(fileSaveAs, SIGNAL(triggered()), this, SLOT(slot_fileSaveAs()));

    fileExit = new QAction(tr("&Exit"), this);
    connect(fileExit, SIGNAL(triggered()), this, SLOT(close()));

    fileMenu->addAction(fileOpen);
    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileSave);
    fileMenu->addAction(fileSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(fileExit);
}

void MainWindow::createClassMenu()
{
    QMenu *classMenu = menuBar()->addMenu(tr("&Classes"));
    QAction *addClasses;

    addClasses = new QAction(tr("&Add"), this);
    connect(addClasses, SIGNAL(triggered()), this, SLOT(slot_addClasses()));

    classMenu->addAction(addClasses);
}

void MainWindow::createViewMenu()
{
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    QActionGroup *displayModeGroup;

    showClassesAct = new QAction(tr("&Classes"), this);
    showClassesAct->setCheckable(true);
    connect(showClassesAct, SIGNAL(triggered()), this, SLOT(showClasses()));

    showFieldsAct = new QAction(tr("&Fields"), this);
    showFieldsAct->setCheckable(true);
    connect(showFieldsAct, SIGNAL(triggered()), this, SLOT(showFields()));

    showObjectsAct = new QAction(tr("&Objects"), this);
    showObjectsAct->setCheckable(true);
    connect(showObjectsAct, SIGNAL(triggered()), this, SLOT(showObjects()));

    displayModeGroup = new QActionGroup(this);
    displayModeGroup->addAction(showClassesAct);
    displayModeGroup->addAction(showFieldsAct);
    displayModeGroup->addAction(showObjectsAct);

    applyToAllAct = new QAction(tr("&Applay to all"), this);
    connect(applyToAllAct, SIGNAL(triggered()), this, SLOT(applyToAll()));

    QAction *switchRelationsShowingAct = new QAction(tr("&Show Relations"), this);
    switchRelationsShowingAct->setCheckable(true);
    switchRelationsShowingAct->setChecked(true);
    connect(switchRelationsShowingAct, SIGNAL(triggered()), this, SLOT(switchRelationsShowing()));

    viewMenu->addAction(showClassesAct);
    viewMenu->addAction(showFieldsAct);
    viewMenu->addAction(showObjectsAct);
    viewMenu->addSeparator();
    viewMenu->addAction(applyToAllAct);
    viewMenu->addAction(switchRelationsShowingAct);
}

void MainWindow::createScaleMenu()
{
    QMenu *scaleMenu;
    QMenu *zoomMenu;
    QAction *zoomIn, *zoomOut;
    QShortcut *keyLeft, *keyRight;

    zoomIn = new QAction(tr("&Zoom In"), this);
    connect(zoomIn, SIGNAL(triggered()), this, SLOT(slot_zoomIn()));

    zoomOut = new QAction(tr("&Zoom Out"), this);
    connect(zoomOut, SIGNAL(triggered()), this, SLOT(slot_zoomOut()));

    scaleMenu = menuBar()->addMenu(tr("&Scale"));
    zoomMenu = new QMenu(tr("&Zoom"));
    scaleMenu->addMenu(zoomMenu);
    zoomMenu->addAction(zoomIn);
    zoomMenu->addAction(zoomOut);

    keyLeft = new QShortcut(this);
    keyLeft->setKey(Qt::CTRL + Qt::Key_Left);
    connect(keyLeft, SIGNAL(activated()), this, SLOT(slot_zoomOut()));

    keyRight = new QShortcut(this);
    keyRight->setKey(Qt::CTRL + Qt::Key_Right);
    connect(keyRight, SIGNAL(activated()), this, SLOT(slot_zoomIn()));
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = new QToolBar;

    relationEditing = new QAction(tr("&Relation editing"), this);
    relationEditing->setCheckable(true);
    relationEditing->setChecked(false);

    connect(relationEditing, SIGNAL(triggered()),
            this, SLOT(switchRelationsEditingMode()));

    toolBar->addAction(relationEditing);
    addToolBar(toolBar);
}

void MainWindow::showTables(AccessMode accesMod, DisplayMode displayMode)
{
    freeResources();

    int tablesCount = dbHandler->getTablesCount();
    tableViews.reserve(tablesCount);

    for (int i = 0; i < tablesCount; i++)
    {
        TableView *tv = new TableView(tablesDrawingArea);

        tv->setID(i);
        tv->setTableName(dbHandler->getTableName(i));
        qDebug() << tv->getTableName();
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

        connect(tv, SIGNAL(deleteClassS(uint)),
                this, SLOT(deleteClass(uint)));

        connect(tv, SIGNAL(clicked(uint)), this, SLOT(tableClicked(uint)));

        tableViews.append(tv);
    }

    setDisplayMode(displayMode);


    QVector<Relation*> *relations = dbHandler->getRelations();

    relationsManager->setRelations(relations);

    tablesDrawingArea->setRelations(relations);
    tablesDrawingArea->setTableViews(&tableViews);
    tablesDrawingArea->setDisplayMode(&(this->displayMode));
}

void MainWindow::setDisplayMode(DisplayMode mode)
{
    displayMode = mode;
    int tablesCount = tableViews.size();

    TableView::setEmitSignals(false);

    switch (mode)
    {
        case CLASSES:
        {
            showClassesAct->setChecked(true);

            for (int i = 0; i < tablesCount; i++)
                tableViews.at(i)->setModel(nullptr);

            break;
        }

        case FIELDS:
        {
            showFieldsAct->setChecked(true);

            for (int i = 0; i < tablesCount; i++)
                tableViews.at(i)->setModel(dbHandler->getTableFieldsModel(i));

            break;
        }

        case OBJECTS:
        {
            showObjectsAct->setChecked(true);

            for (int i = 0; i < tablesCount; i++)
                tableViews.at(i)->setModel(dbHandler->getTableObjectsModel(i));

            break;
        }
    }

    for (int i = 0; i < tablesCount; i++)
    {
        tableViews.at(i)->setGeometry(dbHandler->getTableGeometry(i, mode));
        tableViews.at(i)->setDisplayMod(mode);
    }

    TableView::setEmitSignals(true);

    tablesDrawingArea->adjustSize();
}

void MainWindow::tableXChanged(uint tableID, int x)
{
    tablesDrawingArea->adjustSize();
    tablesDrawingArea->update();

    dbHandler->setTableX(tableID, x, displayMode);
}

void MainWindow::tableYChanged(uint tableID, int y)
{
    tablesDrawingArea->adjustSize();
    tablesDrawingArea->update();

    dbHandler->setTableY(tableID, y, displayMode);
}

void MainWindow::tableWidthChanged(uint tableID, int width)
{
    tablesDrawingArea->adjustSize();
    tablesDrawingArea->update();

    dbHandler->setTableWidth(tableID, width, displayMode);
}

void MainWindow::tableHeightChanged(uint tableID, int height)
{
    tablesDrawingArea->adjustSize();
    tablesDrawingArea->update();

    dbHandler->setTableHeight(tableID, height, displayMode);
}

void MainWindow::tableNameChanged(uint tableID, const QString &name)
{
    tablesDrawingArea->adjustSize();
    tablesDrawingArea->update();

    dbHandler->setTableName(tableID, name);
}

void MainWindow::tableClicked(uint tableId)
{
    if (!isRelationsEditingModeActivated)
        return;

    clicksCount++;

    TableView *view = tableViews.at(tableId);

    if (clicksCount == 1)
    {
        relationsManager->setTableView(0, view);
        relationsManager->setTableFieldsModel(0, (QStandardItemModel*) dbHandler->getTableFieldsModel(view->getID()));

        return;
    }

    if (clicksCount == 2)
    {
        relationsManager->setTableView(1, view);
        relationsManager->setTableFieldsModel(1, (QStandardItemModel*) dbHandler->getTableFieldsModel(view->getID()));

        relationsManager->exec();

        tablesDrawingArea->update();

        clicksCount = 0;

        return;
    }

}

void MainWindow::freeResources()
{
    foreach (TableView *view, tableViews)
        view->deleteLater();

    tableViews.clear();
    tableViews.squeeze();
}
