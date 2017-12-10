#ifndef TABLESDRAWINGAREA_H
#define TABLESDRAWINGAREA_H

#include <QWidget>

class TablesDrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit TablesDrawingArea(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
};

#endif // TABLESDRAWINGAREA_H
