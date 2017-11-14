#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include <QTableView>
#include <QQuickView>

class Controller: QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

private:
    QVector<QTableView*> *tableViews;
    QQuickView *quickView;


signals:

};

#endif // CONTROLLER_H
