#ifndef QTABLEVIEWWRAPPER_H
#define QTABLEVIEWWRAPPER_H

#include <QQuickItem>

#include "GlobalDefinitions.h"

class QTableViewWrapper: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged STORED false)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged STORED false)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged
                                                   STORED false)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged
                                                      STORED false)
    Q_PROPERTY(QWidget* parentWidget READ parentWidget WRITE setParentWidget
                                                       STORED false)
    Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel STORED false)
public:
    explicit QTableViewWrapper(QObject *parent = nullptr);

    int x() const {return tableView.x(); emit xChanged();}
    int y() const {return tableView.y(); emit yChanged();}
    int width() const {return tableView.width(); emit widthChanged();}
    int height() const {return tableView.height(); emit heightChanged();}
    QWidget* parentWidget() const {return tableView.parentWidget();}
    QAbstractItemModel* model() const {return tableView.model();}

    void setX(int x) {tableView.move(x, tableView.y());}
    void setY(int y) {tableView.move(tableView.x(), y);}
    void setWidth(int width) {tableView.resize(width, tableView.height());}
    void setHeight(int height) {tableView.resize(tableView.width(), height);}
    void setParentWidget(QWidget *parent) {tableView.setParent(parent);}
    void setModel(QAbstractItemModel *model) {tableView.setModel(model);}

signals:
    void xChanged() const;
    void yChanged() const;
    void widthChanged( ) const;
    void heightChanged() const;

public slots:
    void setDisplayMod(DisplayMode mode);
    void show() {tableView.show();}

private:
    QTableView tableView;
};

#endif // QTABLEVIEWWRAPPER_H
