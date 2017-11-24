#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QLabel>
#include <QTableView>
#include <QAbstractItemModel>

#include "DraggableWidget.h"

class TableView: public DraggableWidget
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr,
                       const QString &tableName = QString(),
                       const QRect &geometry = QRect(),
                       QAbstractItemModel *model = nullptr);

    void setTableName(const QString &name) {header->setText(name);}
    void setModel(QAbstractItemModel *model) {view->setModel(model);}

private:
    QLabel *header;
    QTableView *view;
};

#endif // TABLEVIEW_H
