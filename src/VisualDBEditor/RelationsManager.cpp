#include "RelationsManager.h"

RelationsManager::RelationsManager(QWidget *parent) :
    QDialog(parent),
    relationsTableWidget(new QTableWidget(0, 3, this)),
    addRelationButton(new QPushButton(QString("Add"), this))
{
    setMinimumWidth(325);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->addWidget(relationsTableWidget);
    layout->addWidget(addRelationButton);
    setLayout(layout);
}

RelationsManager::~RelationsManager()
{
}

int RelationsManager::exec()
{
    Q_ASSERT_X(firstTableView != nullptr, "exec", "firstTableView = nullptr");
    Q_ASSERT_X(secondTableView != nullptr, "exec", "secondTableView = nullptr");
    Q_ASSERT_X(firstTableFieldsModel != nullptr, "exec", "firstTableFieldsModel = nullptr");
    Q_ASSERT_X(secondTableFieldsModel != nullptr, "exec", "firstTableFieldsModel = nullptr");
    Q_ASSERT_X(relations != nullptr, "exec", "relations = nullptr");

    return QDialog::exec();
}

void RelationsManager::setRelations(QVector<Relation *> *r)
{
    relations = r;
}

void RelationsManager::setSecondTableFieldsModel(QAbstractItemModel *value)
{
    secondTableFieldsModel = value;
}

void RelationsManager::setFirstTableFieldsModel(QAbstractItemModel *model)
{
    firstTableFieldsModel = model;
}

void RelationsManager::setSecondTableView(TableView *view)
{
    secondTableView = view;
}

void RelationsManager::setFirstTableView(TableView *view)
{
    firstTableView = view;
}
