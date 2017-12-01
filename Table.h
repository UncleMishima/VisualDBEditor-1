#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>

#define DISPLAYNODE_COUNT 3

class Table : public QObject
{
    Q_OBJECT
private:
    QString name;
    int coordX[DISPLAYNODE_COUNT];
    int coordY[DISPLAYNODE_COUNT];
    int tableWidth[DISPLAYNODE_COUNT];
    int tableHeight[DISPLAYNODE_COUNT];

    int xCoord, yCoord, width, height;

    int fieldsCount, rowsCount;

    QStandardItemModel* fieldsModel;
    QStandardItemModel* rowsModel;
    QStandardItemModel* model;

public:
    explicit Table(QObject *parent = 0);


    QString getName();
    int getCoordX();
    int getCoordY();
    int getWidth();
    int getHeight();

    int getCoordX(int i);
    int getCoordY(int i);
    int getWidth(int i);
    int getHeight(int i);

    int getFieldsCount();
    int getRowsCount();

    //QStandardItemModel* getRowsModel();
    QStandardItemModel* getModel();
    QStandardItemModel* getFieldsModel();
    QStandardItemModel* getRowsModel();

public slots:
    void setName(QString name);

    void setCoord(int x, int y, int i);
    void setResize(int w, int h, int i);

    void setCoordX(int x);
    void setCoordY(int y);
    void setWidth(int w);
    void setHeight(int h);

    void setFieldsAndRows(int f, int r);
    void setRowsModel(QStandardItemModel* );
    void setFieldsModel(QStandardItemModel* );
    void setModel(QStandardItemModel* );

};


#endif // TABLE_H
