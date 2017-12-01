#include "Table.h"

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

void Table::setDisplayMode(int dm)
{
    coords.displayMode = dm;
}

void Table::setCoord(int x, int y)
{
    coords.xCoord = x;
    coords.yCoord = y;
}

void Table::setResize(int w, int h)
{
    coords.width = w;
    coords.height = h;
}

void Table::setFieldsAndRows(int f, int r)
{
    fieldsCount = f;
    rowsCount = r;
}

int Table::getCoordX()
{
    return coords.xCoord;
}

int Table::getCoordY()
{
    return coords.yCoord;
}

int Table::getWidth()
{
    return coords.width;
}

int Table::getHeight()
{
    return coords.height;
}

int Table::getFieldsCount()
{
    return fieldsCount;
}

int Table::getRowsCount()
{
    return rowsCount;
}

int Table::getDisplayMode()
{
    return coords.displayMode;
}
