#include "AddClass.h"
#include "ui_addclass.h"

AddClass::AddClass() : ui(new Ui::Dialog)
{
    ui->setupUi(this);
    if(this->exec() == QDialog::Accepted)
    {
        if(QDialogButtonBox::AcceptRole)
        {
            int cols = ui->colomns->text().toInt();
            int rows = ui->rows->text().toInt();
        }
    }
}


AddClass::~AddClass()
{
    delete ui;
}
