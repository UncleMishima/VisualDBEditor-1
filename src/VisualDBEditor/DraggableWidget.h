#ifndef DRAGGABLEWIDGET_H
#define DRAGGABLEWIDGET_H

#include <QWidget>

class DraggableWidget: public QWidget
{
    Q_OBJECT
public:
    explicit DraggableWidget(QWidget *parent = nullptr);

    bool isDraggable() {return _isDraggable;}
    void setDraggable(bool isDraggable) {_isDraggable = isDraggable;}
    int getDragStep();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPos;
    static const int dragStep = 30;
    static const int startDragDistance = 20;
    bool _isDraggable;
};

#endif // DRAGGABLEWIDGET_H
