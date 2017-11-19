#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>

class Table : public QObject
{
    Q_OBJECT
private:
    QString name;

    int xCoord, yCoord;
    int width, height;
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
    int getFieldsCount();
    int getRowsCount();

    //QStandardItemModel* getRowsModel();
    QStandardItemModel* getModel();
    QStandardItemModel* getFieldsModel();
    QStandardItemModel* getRowsModel();

public slots:
    void setName(QString name);
    void setCoord(int x, int y);
    void setResize(int w, int h);
    void setFieldsAndRows(int f, int r);
    void setRowsModel(QStandardItemModel* );
    void setFieldsModel(QStandardItemModel* );
    void setModel(QStandardItemModel* );

};


#endif // TABLE_H
