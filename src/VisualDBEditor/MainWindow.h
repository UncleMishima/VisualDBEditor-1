#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QScrollArea>

#include "GlobalDefinitions.h"

namespace Ui {
class MainWindow;
}

class DBHandler;
class TableView;
class Controller;
class TablesDrawingArea;
class Relation;
class RelationsManager;
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
    void showClasses() {setDisplayMode(CLASSES);}
    void showFields() {setDisplayMode(FIELDS);}
    void showObjects() {setDisplayMode(OBJECTS);}
    void applyToAll();
    void addNewClass();
    void deleteClass(uint id);
    void switchRelationsEditingMode();

    void tableXChanged(uint tableID, int x);
    void tableYChanged(uint tableID, int y);
    void tableWidthChanged(uint tableID, int width);
    void tableHeightChanged(uint tableID, int height);
    void tableNameChanged(uint tableID, const QString &name);
    void tableClicked(uint tableId);

private:
    Ui::MainWindow *ui;

    //font view menu elelments
    //QMenu *tableMenu;
    //QAction *chooseFont;

    QAction *showClassesAct, *showFieldsAct, *showObjectsAct, *applyToAllAct;
    QAction *relationEditing;

    AddClass *newClass;
    DBHandler *dbHandler;
    Controller* controller;
    DisplayMode displayMode;
    QVector<TableView*> tableViews;
    RelationsManager *relationsManager;
    bool isRelationsEditingModeActivated;
    int clicksCount = 0; // used to determine when RelationManager must be shown

    // TableView widgets and relations are drawn inside this widget
    TablesDrawingArea *tablesDrawingArea;
    QScrollArea *scrollArea;

    void createMenu();
    void createFileMenu();
    void createClassMenu();
    void createViewMenu();
    void createToolBar();

    void freeResources();
    void setDisplayMode(DisplayMode mode);
};

#endif // MAINWINDOW_H
