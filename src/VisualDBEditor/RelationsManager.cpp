#include "RelationsManager.h"
#include "TableView.h"
#include "Relation.h"

RelationsManager::RelationsManager(QWidget *parent) :
    QDialog(parent),
    relationsTableWidget(new QTableWidget(0, 3, this)),
    addRelationButton(new QPushButton(QString("Add"), this))
{
    setMinimumWidth(327);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->addWidget(relationsTableWidget);
    layout->addWidget(addRelationButton);
    setLayout(layout);

    connect(addRelationButton, SIGNAL(clicked()), this, SLOT(addRelation()));
}

RelationsManager::~RelationsManager()
{
}

int RelationsManager::exec()
{
    Q_ASSERT_X(tableViews[0] != nullptr, "exec", "first tableViews is not set");
    Q_ASSERT_X(tableViews[1] != nullptr, "exec", "second tableViews is not set");
    Q_ASSERT_X(tableFieldsModels[0] != nullptr, "exec", "first table field modle is not set");
    Q_ASSERT_X(tableFieldsModels[1] != nullptr, "exec", "second table field modle is not set");
    Q_ASSERT_X(relations != nullptr, "exec", "relations is not set");

    if (tableViews[0] == tableViews[1])
        return 0;

    initialize();

    QDialog::exec();

    freeResources();

    return 0;
}

void RelationsManager::addRelation()
{
    Relation *r = new Relation;
    r->setTableId(0, tableViews[0]->getID());
    r->setTableId(1, tableViews[1]->getID());

    int index = relations->size();
    currentRelationsIndices.push_back(index);
    relations->push_back(r);

    addRow();
}

void RelationsManager::initialize()
{
    uint id1 = tableViews[0]->getID();
    uint id2 = tableViews[1]->getID();
    for (int i = 0; i < relations->size(); i++)
    {
        Relation *r = relations->at((i));

        if (r->getTableId(0) == id1 && r->getTableId(1) == id2)
        {
            currentRelationsIndices.push_back((i));
            continue;
        }

        if (r->getTableId(0) == id2 && r->getTableId(1) == id1)
        {
            std::swap(tableViews[0], tableViews[1]);
            std::swap(tableFieldsModels[0], tableFieldsModels[1]);
            currentRelationsIndices.push_back((i));

            continue;
        }
    }

    QStringList hhLabels;
    hhLabels << tableViews[0]->getTableName() << tableViews[1]->getTableName() << "";
    relationsTableWidget->setHorizontalHeaderLabels(hhLabels);

    for (int i = 0; i < currentRelationsIndices.size(); i++)
    {
        addRow();

        Relation *r = relations->at(i);

        QString firstTableFieldName = tableFieldsModels[0]->item(r->getTableFieldNumber(0), 0)->data(Qt::DisplayRole).toString();
        relationsTableWidget->setItem(i, 0, new QTableWidgetItem(firstTableFieldName));

        QString secondTableFieldName = tableFieldsModels[1]->item(r->getTableFieldNumber(1), 0)->data(Qt::DisplayRole).toString();
        relationsTableWidget->setItem(i, 1, new QTableWidgetItem(secondTableFieldName));
    }

    connect(relationsTableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));
}

void RelationsManager::freeResources()
{
    currentRelationsIndices.clear();

    while (relationsTableWidget->rowCount() != 0)
        relationsTableWidget->removeRow(0);

    disconnect(relationsTableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));
}

void RelationsManager::addRow()
{
    int row = relationsTableWidget->rowCount();
    relationsTableWidget->insertRow(row);

    QPushButton *deleteButton = new QPushButton(QString("Delete"));
    relationsTableWidget->setCellWidget(row, 2, deleteButton);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(removeRelation()));
}

void RelationsManager::removeRelation()
{
    int result = QMessageBox::question(this, tr("VisualDBEditor"),
                                       tr("Are you shure?"));

    if (result == QMessageBox::No)
        return;

    int row = relationsTableWidget->currentRow();
    relationsTableWidget->removeRow(row);
    relations->remove(currentRelationsIndices.at(row));
    currentRelationsIndices.remove(row);
}

void RelationsManager::cellChanged(int row, int column)
{
    QString fieldName = relationsTableWidget->item(row,column)->data(Qt::DisplayRole).toString();
    QList<QStandardItem*> items = tableFieldsModels[column]->findItems(fieldName);

    if (items.isEmpty())
    {
        QMessageBox::critical(this, tr("VisualDBEditor"),
                                    tr("Invalid field"));

        relationsTableWidget->item(row, column)->setData(Qt::DisplayRole, QVariant::fromValue(QString()));

        return;
    }

    uint fieldNumber = items.first()->row();
    relations->at(currentRelationsIndices.at(row))->setTableFieldNumber(column, fieldNumber);
}

void RelationsManager::setTableView(uint index, TableView *view)
{
    Q_ASSERT_X(index < 2, "setTableView", "index out of range");
    tableViews[index] = view;
}

void RelationsManager::setTableFieldsModel(int index, QStandardItemModel *model)
{
    Q_ASSERT_X(index < 2, "setTableFieldsModel", "index out of range");
    tableFieldsModels[index] = model;
}

void RelationsManager::setRelations(QVector<Relation *> *r)
{
    relations = r;
}

