#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizeGrip>

#include "TableView.h"

TableView::TableView(QWidget *parent): DraggableWidget(parent),
                                       tableName(new QLabel),
                                       view(new QTableView)
{
    setWindowFlags(Qt::SubWindow);
    new QSizeGrip(this);

    tableName->setFrameStyle(QFrame::StyledPanel);
    tableName->setAlignment(Qt::AlignCenter);
    tableName->setStyleSheet("background-color: grey;"
                          "font: 10pt;");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->addWidget(this->tableName);
    layout->addWidget(view);
    setLayout(layout);
}

void TableView::setModel(QAbstractItemModel *model)
{
    view->setModel(model);

    if (model == nullptr)
        view->setVisible(false);
    else
        view->setVisible(true);
}

void TableView::setAccesMod(AccessMod mod)
{
    switch (mod)
    {
        case VIEW_ONLY:
        {
            setDraggable(false);
            view->setEditTriggers(QAbstractItemView::NoEditTriggers);
            break;
        }

        case DATA_EDIT:
        {
            setDraggable(false);
            view->setEditTriggers(QAbstractItemView::DoubleClicked);
            break;

        }

        case STRUCTURE_EDIT:
        {
            setDraggable(true);
            view->setEditTriggers(QAbstractItemView::DoubleClicked);
            break;
        }
    }
}
