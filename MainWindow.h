#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include <GlobalDefinitions.h>

namespace Ui {
class MainWindow;
}

class DBHandler;
class TableView;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(DBHandler *h, QWidget *parent = 0);
    ~MainWindow();

    void showTables(AccessMod accesMod, DisplayMode displayMod);

private slots:
    void slot_fileOpen();
    void slot_fileSave();
    void xChanged(uint tableId, int x);
    void yChanged(uint tableId, int y);
    void widthChanged(uint tableId, int wtableIdth);
    void heightChanged(uint tableId, int height);
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
