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
    Q_PROPERTY(QTableView* tableView READ tableView)
public:
    explicit QTableViewWrapper(QObject *parent = nullptr);

    int x() const {return _tableView.x(); emit xChanged();}
    int y() const {return _tableView.y(); emit yChanged();}
    int width() const {return _tableView.width(); emit widthChanged();}
    int height() const {return _tableView.height(); emit heightChanged();}
    QWidget* parentWidget() const {return _tableView.parentWidget();}
    QAbstractItemModel* model() const {return _tableView.model();}
    QTableView* tableView() {return &_tableView;}

    void setX(int x) {_tableView.move(x, _tableView.y());}
    void setY(int y) {_tableView.move(_tableView.x(), y);}
    void setWidth(int width) {_tableView.resize(width, _tableView.height());}
    void setHeight(int height) {_tableView.resize(_tableView.width(), height);}
    void setParentWidget(QWidget *parent) {_tableView.setParent(parent);}
    void setModel(QAbstractItemModel *model) {_tableView.setModel(model);}

signals:
    void xChanged() const;
    void yChanged() const;
    void widthChanged( ) const;
    void heightChanged() const;

public slots:
    void setDisplayMod(DisplayMode mode);
    void show() {_tableView.show();}

private:
    QTableView _tableView;
};

#endif // QTABLEVIEWWRAPPER_H
