#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "GlobalDefinitions.h"

class Controller: QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

signals:
    void openConnection(DBType tm, QString url, QString dbName,
                        QString userName, QString password, ConnectionFlags f);

private:
    QVector<QTableView*> *tableViews;
    QQuickView *quickView;

};

#endif // CONTROLLER_H
