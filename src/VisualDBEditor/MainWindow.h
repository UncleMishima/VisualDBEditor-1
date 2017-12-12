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
    void slot_chooseFont();
    void showClasses() {setDisplayMode(CLASSES);}
    void showFields() {setDisplayMode(FIELDS);}
    void showObjects() {setDisplayMode(OBJECTS);}

    void tableXChanged(uint tableID, int x);
    void tableYChanged(uint tableID, int y);
    void tableWidthChanged(uint tableID, int width);
    void tableHeightChanged(uint tableID, int height);
    void tableNameChanged(uint tableID, const QString &name);

private:
    Ui::MainWindow *ui;

    QMenu *fileMenu;
    QAction *fileOpen, *fileExit, *fileSave, *fileSaveAs;

    QMenu *tableMenu;
    QAction *chooseFont;

    QMenu *viewMenu;
    QActionGroup *displayModeGroup;
    QAction *showClassesAct, *showFieldsAct, *showObjectsAct;

    DBHandler *dbHandler;
    Controller* controller;
    DisplayMode displayMode;
    QVector<TableView*> *tableViews;

    // TableView widgets and relations are drawn inside this widget
    TablesDrawingArea *tablesDrawingArea;
    QScrollArea *scrollArea;

    void createActions();
    void createMenu();
    void freeResources();
    void setDisplayMode(DisplayMode mode);
};

#endif // MAINWINDOW_H
