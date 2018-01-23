#include <QVBoxLayout>
#include <QSizeGrip>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QMenu>
#include <QMessageBox>

#include "TableView.h"

bool TableView::_isEmitSignals = true;

TableView::TableView(QWidget *parent):
    DraggableWidget(parent),
    tableName(new QLabel),
    view(new QTableView)
{
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWindowFlags(Qt::SubWindow);
    new QSizeGrip(this);

    tableName->setFrameStyle(QFrame::StyledPanel);
    tableName->setAlignment(Qt::AlignCenter);
    tableName->setStyleSheet("background-color: grey;");
    tableName->setFont(QFont("Arial", 14));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->addWidget(this->tableName);
    layout->addWidget(view);
    setLayout(layout);

    createActions();
}

void TableView::setModel(QAbstractItemModel *model)
{
    view->setModel(model);
    view->setFont(QFont("Arial", 14));
}

void TableView::setDisplayMod(DisplayMode mode)
{
    if (mode == CLASSES)
    {
        view->setVisible(false);
        addRowAct->setVisible(false);
        deleteRowAct->setVisible(false);
    }
    else
    {
        view->setVisible(true);
        addRowAct->setVisible(true);
        deleteRowAct->setVisible(true);

        if (mode == FIELDS)
        {
            addRowAct->setText(tr("&Add Field"));
            deleteRowAct->setText(tr("&Delete Field"));

            return;
        }
        else
        {
            addRowAct->setText(tr("&Add Object"));
            deleteRowAct->setText(tr("&Delete Object"));
        }
    }
}

void TableView::setTableName(const QString &name)
{
    tableName->setText(name);

    if (_isEmitSignals)
        emit tableNameChanged(id, name);
}

void TableView::setCoords(uint id, int x, int y)
{
    this->move(x, y);
    emit xChanged(id, x);
    emit yChanged(id, y);
}

/*
void TableView::setYCoord(int y)
{
    emit yChanged(y);
}

void TableView::setWidth(int w)
{
    emit widthChanged(w);
}

void TableView::setHeight(int h)
{
    emit heightChanged(h);
}
*/

void TableView::setAccesMod(AccessMode mode)
{
    switch (mode)
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
    if (!_isEmitSignals)
        return;

    const QPoint &oldPos = event->oldPos();
    const QPoint &pos = event->pos();

    if (oldPos.x() != pos.x())
        emit xChanged(id, pos.x());

    if (oldPos.y() != pos.y())
        emit yChanged(id, pos.y());
}

void TableView::resizeEvent(QResizeEvent *event)
{
    if (!_isEmitSignals)
        return;

    const QSize &oldSize = event->oldSize();
    const QSize &size = event->size();

    if (oldSize.width() != size.width())
        emit widthChanged(id, size.width());

    if (oldSize.height() != size.height())
        emit heightChanged(id, size.height());
}

void TableView::enterEvent(QEvent*)
{
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void TableView::leaveEvent(QEvent*)
{
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TableView::contextMenuEvent(QContextMenuEvent *event)
{
   QMenu menu(this);

   menu.addAction(addRowAct);
   menu.addAction(deleteRowAct);
   menu.addAction(deleteClassAct);

   if (view->selectionModel()->selectedIndexes().isEmpty())
       deleteRowAct->setEnabled(false);
   else
       deleteRowAct->setEnabled(true);

   menu.exec(event->globalPos());
}

void TableView::addRow()
{
    QModelIndexList indexList = view->selectionModel()->selectedIndexes();
    QAbstractItemModel *model = view->model();
    int row = indexList.isEmpty() ? model->rowCount()
                                  : indexList.last().row();

    model->insertRow(row);
}

void TableView::deleteRow()
{
    int result = QMessageBox::question(this, tr("VisualDBEditor"),
                                       tr("Are you shure?"));

    if (result == QMessageBox::No)
        return;

    QAbstractItemModel *model = view->model();
    QModelIndexList indexList;

    while (true)
    {

        indexList = view->selectionModel()->selectedIndexes();

        if (indexList.isEmpty())
            return;

        model->removeRow(indexList.first().row());
    }
}

void TableView::createActions()
{
    addRowAct = new QAction(this);
    connect(addRowAct, SIGNAL(triggered()), this, SLOT(addRow()));

    deleteRowAct = new QAction(this);
    connect(deleteRowAct, SIGNAL(triggered()), SLOT(deleteRow()));

    deleteClassAct = new QAction(tr("Delete class"), this);
    connect(deleteClassAct, SIGNAL(triggered()), SLOT(deleteClass()));

}

void TableView::deleteClass()
{
    emit deleteClass(id);
}
