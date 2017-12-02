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

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(DBHandler *h);
    ~MainWindow();

    void showTables(AccessMod accesMod, DisplayMode displayMode);

private slots:
    void slot_fileOpen();
    void slot_fileSave();
    void tableXChanged(uint tableID, int x);
    void tableYChanged(uint tableID, int y);
    void tableWidthChanged(uint tableID, int width);
    void tableHeightChanged(uint tableID, int height);
    void tableNameChanged(uint tableID, const QString &name);

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
