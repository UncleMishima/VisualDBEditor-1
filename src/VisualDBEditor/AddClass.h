#ifndef ADDCLASS_H
#define ADDCLASS_H

#include <QDialog>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QTableView>

namespace Ui {
class Dialog;
}

class AddClass : public QDialog
{
public:
    AddClass();
    ~AddClass();

    //QTableWidget* table;
    //QTableView* table;
    //QStandardItemModel* model;

    //void addNewClass();

    const unsigned int ITEM_COUNT = 20;
    Ui::Dialog* ui;

private:


};

#endif // ADDCLASS_H
