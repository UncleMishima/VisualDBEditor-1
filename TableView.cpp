#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QMoveEvent>
#include <QResizeEvent>

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

void TableView::setTableName(const QString &name)
{
    tableName->setText(name);

    emit tableNameChanged(id, name);
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

void TableView::moveEvent(QMoveEvent *event)
{
    const QPoint &oldPos = event->oldPos();
    const QPoint &pos = event->pos();

    if (oldPos.x() != pos.x())
        emit xChanged(id, pos.x());

    if (oldPos.y() != pos.y())
        emit yChanged(id, pos.y());
}

void TableView::resizeEvent(QResizeEvent *event)
{
    const QSize &oldSize = event->oldSize();
    const QSize &size = event->size();

    if (oldSize.width() != size.width())
        emit widthChanged(id, size.width());

    if (oldSize.height() != size.height())
        emit heightChanged(id, size.height());

}
