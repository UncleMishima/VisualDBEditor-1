#include "Controller.h"

Controller::Controller(QObject *parent): QObject(parent)
{
    quickView.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
}

Controller::~Controller(){}

void Controller::start()
{
    quickView.show();
}
