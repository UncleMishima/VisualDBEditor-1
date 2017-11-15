#include "Controller.h"

Controller::Controller(QObject *parent): QObject(parent)
{
    quickWidget.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    quickWidget.setResizeMode(QQuickWidget::SizeRootObjectToView);
}

Controller::~Controller(){}

void Controller::start()
{
    quickWidget.show();
}
