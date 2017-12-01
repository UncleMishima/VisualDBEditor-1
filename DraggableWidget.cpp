#include <QMouseEvent>

#include "DraggableWidget.h"

DraggableWidget::DraggableWidget(QWidget *parent): QWidget(parent),
                                                   _isDraggable(true)
{

}

void DraggableWidget::mousePressEvent(QMouseEvent *event)
{
    if (_isDraggable && event->button() == Qt::LeftButton)
        dragStartPos = event->globalPos();
}

void DraggableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!_isDraggable)
        return;

    if (!(event->buttons() & Qt::LeftButton))
        return;

    QPoint dragDistance = event->globalPos() - dragStartPos;
    QPoint step;

    if (dragDistance.x() <= -startDragDistance ||
        dragDistance.x() >=  startDragDistance)
    {
        step.rx() = (dragDistance.x() < 0) ? -dragStep : dragStep;
    }

    if (dragDistance.y() <= -startDragDistance ||
        dragDistance.y() >=  startDragDistance)
    {
        step.ry() = (dragDistance.y() < 0) ? -dragStep : dragStep;
    }

    if (!step.isNull())
    {
        dragStartPos += step;

        QPoint newPos = pos() + step;
        int &x = newPos.rx(), &y = newPos.ry();

        x = (x < 0) ? 0 : x;
        y = (y < 0) ? 0 : y;

        move(newPos);
    }
}
