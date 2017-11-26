#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QLabel>
#include <QTableView>
#include <QAbstractItemModel>

#include "DraggableWidget.h"
#include "GlobalDefinitions.h"

class TableView: public DraggableWidget
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);

    void setTableName(const QString &name) {tableName->setText(name);}
    void setModel(QAbstractItemModel *model);

private:
    QLabel *tableName;
    QTableView *view;
};

#endif // TABLEVIEW_H
