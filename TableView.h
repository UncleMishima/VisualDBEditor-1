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

    void setId(uint i) {id = i;}
    void setTableName(const QString &name) {tableName->setText(name);}
    void setModel(QAbstractItemModel *model);
    void setAccesMod(AccessMod mod);

    uint getId() const {return id;}
    QString getTableName() const {return tableName->text();}
    QAbstractItemModel* getModel() const {return view->model();}

private:
    uint id;
    QLabel *tableName;
    QTableView *view;
};

#endif // TABLEVIEW_H
