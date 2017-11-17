#include "Controller.h"

#include <QDebug>
#include <QQmlContext>

Controller::Controller(QObject *parent): QObject(parent)
{
    quickWidget.rootContext()->setContextProperty("controller", this);

    quickWidget.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    quickWidget.setResizeMode(QQuickWidget::SizeRootObjectToView);

}

Controller::~Controller()
{
    freeResources();
}

void Controller::start()
{
    quickWidget.show();
}

void Controller::createTableFrame(QString name, int x, int y, QQuickItem *parentItem)
{
    QQmlComponent component(quickWidget.engine(), QUrl(QStringLiteral("qrc:/TableFrame.qml")));
    QObject *tableFrame = component.create();
    QQuickItem *item = qobject_cast<QQuickItem*>(tableFrame);

    QQuickItem *root = quickWidget.rootObject();
    qDebug() << "root: " << root->property("id");

    QList<QQuickItem*> childItems= root->childItems();
    foreach (QQuickItem *child, childItems)
        qDebug() << "child: " << child->property("id");

    item->setParentItem(parentItem);
    item->setX(x);
    item->setY(y);

    tableFrame->setProperty("headerText", name);

    tableFrames.push_back(tableFrame);
}

void Controller::freeResources()
{
    if (tableViews != nullptr)
    {
        foreach (QTableView *view, *tableViews)
            delete view;
    }

    foreach (QObject *frame, tableFrames)
        delete frame;
}

