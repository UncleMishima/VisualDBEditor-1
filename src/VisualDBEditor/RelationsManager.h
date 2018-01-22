#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include "GlobalDefinitions.h"

class TableView;
class Relation;

class RelationsManager : public QDialog
{
    Q_OBJECT

public:
    explicit RelationsManager(QWidget *parent = 0);
    ~RelationsManager();

    void setFirstTableView(TableView *view);
    void setSecondTableView(TableView *view);
    void setFirstTableFieldsModel(QAbstractItemModel *model);
    void setSecondTableFieldsModel(QAbstractItemModel *model);
    void setRelations(QVector<Relation *> *r);

public slots:
    virtual int exec() override;

private:
    TableView *firstTableView = nullptr;
    TableView *secondTableView = nullptr;
    QAbstractItemModel *firstTableFieldsModel = nullptr;
    QAbstractItemModel *secondTableFieldsModel = nullptr;
    QVector<Relation*> *relations = nullptr;

    QTableWidget *relationsTableWidget;
    QPushButton *addRelationButton;
};

#endif // RELATIONMANAGER_H
