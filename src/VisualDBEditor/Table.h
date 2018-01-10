#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>

#include "GlobalDefinitions.h"

#define DISPLAY_MODES_COUNT 3

class Table : public QObject
{
    Q_OBJECT
public:
    explicit Table();
    ~Table();

    QString getName();
    int getCoordX(DisplayMode mode);
    int getCoordY(DisplayMode mode);
    int getWidth(DisplayMode mode);
    int getHeight(DisplayMode mode);
    QRect getGeometry(DisplayMode mode);
    QStandardItemModel *getFieldsModel();
    QStandardItemModel *getObjectsModel();

    void setName(const QString &name);

    void setCoord(int x, int y, DisplayMode mode);
    void resize(int w, int h, DisplayMode mode);

    void setCoordX(int x, DisplayMode mode);
    void setCoordY(int y, DisplayMode mode);
    void setWidth(int w, DisplayMode mode);
    void setHeight(int h, DisplayMode mode);
    void setGeometry(const QRect &rect, DisplayMode mode);

    void setObjectsModel(QStandardItemModel* im);
    void setFieldsModel(QStandardItemModel* im);

private slots:
    void fieldsModelChanged() {isFieldsModelChanged = true;}

private:
    QString name;
    int coordX[DISPLAY_MODES_COUNT];
    int coordY[DISPLAY_MODES_COUNT];
    int tableWidth[DISPLAY_MODES_COUNT];
    int tableHeight[DISPLAY_MODES_COUNT];
    bool isFieldsModelChanged = false;

    QStandardItemModel* fieldsModel = nullptr;
    QStandardItemModel* objectsModel = nullptr;

};

#endif // TABLE_H
