#ifndef TABLESDRAWINGAREA_H
#define TABLESDRAWINGAREA_H

#include <QWidget>

#include "GlobalDefinitions.h"

class Relation;
class TableView;

class TablesDrawingArea: public QWidget
{
    Q_OBJECT
public:
    explicit TablesDrawingArea(QWidget *parent = nullptr);

    void setDisplayMode(DisplayMode *mode) {displayMode = mode;}
    void setTableViews(QVector<TableView*> *views) {tableViews = views;}
    void setRelations(QVector<Relation*> *r) {relations = r;}

protected:
    void paintEvent(QPaintEvent *);

private:
    DisplayMode *displayMode =  nullptr;
    QVector<TableView*> *tableViews =  nullptr;
    QVector<Relation*> *relations = nullptr;
};

#endif // TABLESDRAWINGAREA_H
