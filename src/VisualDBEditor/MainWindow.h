#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QScrollArea>
#include <QShortcut>

#include "GlobalDefinitions.h"

namespace Ui {
class MainWindow;
}

class DBHandler;
class TableView;
class Controller;
class TablesDrawingArea;
class Relation;
class AddClass;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(DBHandler *h, Controller *c);
    ~MainWindow();

    void showTables(AccessMode accesMod, DisplayMode displayMode);

private slots:
    void slot_fileOpen();
    void slot_fileSaveAs();
    void slot_fileSave();
    //void slot_chooseFont();
    void slot_addClasses();
    void slot_zoomIn();
    void slot_zoomOut();
    void showClasses() {setDisplayMode(CLASSES);}
    void showFields() {setDisplayMode(FIELDS);}
    void showObjects() {setDisplayMode(OBJECTS);}
    void applyToAll();
    void addNewClass();
    void deleteClass(uint id);

    void tableXChanged(uint tableID, int x);
    void tableYChanged(uint tableID, int y);
    void tableWidthChanged(uint tableID, int width);
    void tableHeightChanged(uint tableID, int height);
    void tableNameChanged(uint tableID, const QString &name);

private:
    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QAction *fileOpen, *fileExit, *fileSave, *fileSaveAs;

    QMenu *classMenu;
    QAction *addClasses;

    //font view menu elelments
    //QMenu *tableMenu;
    //QAction *chooseFont;

    QMenu *viewMenu;
    QActionGroup *displayModeGroup;
    QAction *showClassesAct, *showFieldsAct, *showObjectsAct, *applyToAllAct;

    QMenu *scaleMenu;
    QMenu *zoomMenu;
    QAction *zoomIn, *zoomOut;

    int zoomCounter;
    int zoomFactor;

    double mwCenterXCoord;
    double mwCenterYCoord;

    QShortcut *keyLeft, *keyRight;

    AddClass *newClass;
    DBHandler *dbHandler;
    Controller* controller;
    DisplayMode displayMode;
    QVector<TableView*> tableViews;

    // TableView widgets and relations are drawn inside this widget
    TablesDrawingArea *tablesDrawingArea;
    QScrollArea *scrollArea;

    void createActions();
    void createShortcuts();
    void createMenu();
    void freeResources();
    void setDisplayMode(DisplayMode mode);
    void moveTables(int zoomF);
};

#endif // MAINWINDOW_H
