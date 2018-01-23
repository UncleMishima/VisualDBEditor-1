#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QtGlobal>
#include <algorithm>

#include "GlobalDefinitions.h"

class TableView;
class Relation;

class RelationsManager : public QDialog
{
    Q_OBJECT

public:
    explicit RelationsManager(QWidget *parent = 0);
    ~RelationsManager();

    void setTableView(uint index, TableView *view);
    void setTableFieldsModel (int index, QStandardItemModel *model);
    void setRelations(QVector<Relation *> *r);

public slots:
    virtual int exec() override;
    void addRelation();
    void removeRelation();
    void cellChanged(int row, int column);

private:
    TableView *tableViews[2] = {nullptr, nullptr};
    QStandardItemModel *tableFieldsModels[2] = {nullptr, nullptr};
    // Indeces of relations betwen current tables
    QVector<int> currentRelationsIndices;
    QVector<Relation*> *relations = nullptr;

    QTableWidget *relationsTableWidget;
    QPushButton *addRelationButton;

    void addRow();
    void initialize();
    void freeResources();
};

#endif // RELATIONMANAGER_H
