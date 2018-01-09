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

    void setID(uint i) {id = i;}
    void setTableName(const QString &name);
    void setModel(QAbstractItemModel *model);
    void setDisplayMod(DisplayMode mode);
    void setAccesMod(AccessMode mode);
    static void setEmitSignals(bool b) {_isEmitSignals = b;}

    uint getID() const {return id;}
    QString getTableName() const {return tableName->text();}
    QAbstractItemModel* getModel() const {return view->model();}
    static bool isEmitSignals() {return _isEmitSignals;}

signals:
    void xChanged(uint id, int x);
    void yChanged(uint id, int y);
    void widthChanged(uint id, int width);
    void heightChanged(uint id, int height);
    void tableNameChanged(uint id, const QString &name);

protected:
    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    void addRow();
    void deleteRow();

private:
    uint id;
    QLabel *tableName;
    QTableView *view;
    QItemSelectionModel *selectionModel;
    static bool _isEmitSignals;

    QAction *addRowAct, *deleteRowAct;

    void createActions();
};

#endif // TABLEVIEW_H
