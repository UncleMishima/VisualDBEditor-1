#include "AddClass.h"
#include "ui_addclass.h"

#include <QDebug>

AddClass::AddClass() : ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->fieldsTableWidget->setColumnCount(ITEM_COUNT);
    ui->fieldsTableWidget->setRowCount(2);

    ui->objectsTableWidget->setColumnCount(ITEM_COUNT);
    ui->objectsTableWidget->setRowCount(ITEM_COUNT);
/*
    if(this->exec() == QDialog::Accepted)
    {
        addNewClass();
    }
    else if(this->exec() == QDialog::Rejected)
    {
        qDebug() << "Table has not created";
    }
    */
}

/*
void AddClass::addNewClass()
{
    model = new QStandardItemModel();
    for(int i = 0; i < ITEM_COUNT; i++)
    {
        for(int j = 0; j < ITEM_COUNT; j++)
        {
            if(ui->tableWidget->item(i, j) == nullptr)
            {
                continue;
            }
            else
            {
                //qDebug() << i << " " << j;
                model->setItem(i, j, new QStandardItem(ui->tableWidget->item(i, j)->text()));
                //qDebug() << model->
            }
        }
    }

    table = new QTableView();
    table->setModel(model);
    table->show();
}
*/
AddClass::~AddClass()
{
    delete ui;
}
