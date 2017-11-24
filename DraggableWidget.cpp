#include <QMouseEvent>

#include "DraggableWidget.h"

DraggableWidget::DraggableWidget(QWidget *parent) : QWidget(parent)
{

}

void DraggableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPos = event->globalPos();
}

void DraggableWidget::mouseMoveEvent(QMouseEvent *event)
{
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
        move(pos() + step);
    }
}
