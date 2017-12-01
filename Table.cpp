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

void Table::setCoordX(int x)
{
    xCoord = x;
}

void Table::setCoordY(int y)
{
    yCoord = y;
}

void Table::setWidth(int w)
{
    width = w;
}

void Table::setHeight(int h)
{
    height = h;
}


void Table::setCoord(int x, int y, int i)
{
    coordX[i] = x;
    coordY[i] = y;
}

void Table::setResize(int w, int h, int i)
{
    tableWidth[i] = w;
    tableHeight[i] = h;
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

int Table::getCoordX(int i)
{
    return coordX[i];
}

int Table::getCoordY(int i)
{
    return coordY[i];
}

int Table::getWidth(int i)
{
    return tableWidth[i];
}

int Table::getHeight(int i)
{
    return tableHeight[i];
}

int Table::getFieldsCount()
{
    return fieldsCount;
}

int Table::getRowsCount()
{
    return rowsCount;
}
