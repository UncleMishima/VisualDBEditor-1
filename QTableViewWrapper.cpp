#include "QTableViewWrapper.h"

QTableViewWrapper::QTableViewWrapper(QObject *parent) : QObject(parent)
{

}

void QTableViewWrapper::setDisplayMod(DisplayMode mode)
{
    switch (mode)
    {
        case OBJECTS:
        _tableView.show();

        default:
        break;
    }
}
