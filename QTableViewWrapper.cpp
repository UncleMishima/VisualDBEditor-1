#include "QTableViewWrapper.h"

QTableViewWrapper::QTableViewWrapper(QObject *parent) : QObject(parent)
{

}

void QTableViewWrapper::setDisplayMod(DisplayMode mode)
{
    switch (mode)
    {
        case OBJECTS:
        tableView.show();

        default:
        break;
    }
}
