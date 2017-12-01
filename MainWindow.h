#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "GlobalDefinitions.h"

namespace Ui {
class MainWindow;
}

class DBHandler;
class TableView;
    // debug
    class Table;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(DBHandler *h, QWidget *parent = 0);
    ~MainWindow();

    void showTables(AccessMod accesMod, DisplayMode displayMod);

    // debug
    void createTableView(Table *table);

private slots:
    void slot_fileOpen();
    void slot_fileSave();
    void tableXChanged(uint tableId, int x);
    void tableYChanged(uint tableId, int y);
    void tableWidthChanged(uint tableId, int wtableIdth);
    void tableHeightChanged(uint tableId, int height);
    void tableNameChanged(uint tableId, QString name);

private:
    Ui::MainWindow *ui;
    QMenu* fileMenu;
    QAction *fileOpen, *fileExit, *fileSave;
    DBHandler *dbHandler;
    DisplayMode displayMode;
    QVector<TableView*> *tableViews;
    // TableView widgets and relations are drawn inside this widget
    QWidget *tablesScene;
    QScrollArea *scrollArea;

    void createMenu();
    void freeResources();
};

#endif // MAINWINDOW_H
