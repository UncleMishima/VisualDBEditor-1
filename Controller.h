#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QQuickItem>

#include "GlobalDefinitions.h"

class Controller: QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void start();
    Q_INVOKABLE void createTableFrame(QString name, int x, int y, QQuickItem *parentItem);

signals:
    void openConnection(DBType tm, QString url, QString dbName,
                        QString userName, QString password, ConnectionFlags f);

private:
    QVector<QTableView*> *tableViews;
    QVector<QObject*> tableFrames;
    QQuickWidget quickWidget;

    void freeResources();

};

#endif // CONTROLLER_H
