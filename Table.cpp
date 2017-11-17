#include "table.h"

Table::Table(QObject *parent) : QObject(parent)
{
    //fieldsModel = nullptr;
    //rowsModel = nullptr;
}


QString Table::getName()
{
    return name;
}

QStandardItemModel* Table::getModel()
{
    return model;
}

QStandardItemModel* Table::getFieldsModel()
{
    return fieldsModel;
}

QStandardItemModel* Table::getRowsModel()
{
    return rowsModel;
}


void Table::setName(QString name)
{
    this->name = name;
}

void Table::setModel(QStandardItemModel *im)
{
    model = im;
}

void Table::setFieldsModel(QStandardItemModel *im)
{
    fieldsModel = im;
}

void Table::setRowsModel(QStandardItemModel *im)
{
    rowsModel = im;
}

void Table::setCoord(int x, int y)
{
    xCoord = x;
    yCoord = y;
}

void Table::setResize(int w, int h)
{
    width = w;
    height = h;
}

void Table::setFieldsAndRows(int f, int r)
{
    fieldsCount = f;
    rowsCount = r;
}

int Table::getCoordX()
{
    return xCoord;
}

int Table::getCoordY()
{
    return yCoord;
}

int Table::getWidth()
{
    return width;
}

int Table::getHeight()
{
    return height;
}

int Table::getFieldsCount()
{
    return fieldsCount;
}

int Table::getRowsCount()
{
    return rowsCount;
}
