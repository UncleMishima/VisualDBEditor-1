#include <QVBoxLayout>

#include "TableView.h"

TableView::TableView(QWidget *parent,
                     const QString &tableName,
                     const QRect &geometry,
                     QAbstractItemModel *model)
                     : DraggableWidget(parent),
                       header(new QLabel(tableName)),
                       view(new QTableView)
{
    setGeometry(geometry);

    if (model != nullptr)
        view->setModel(model);

    header->setFrameStyle(QFrame::StyledPanel);
    header->setAlignment(Qt::AlignCenter);
    header->setStyleSheet("background-color: grey;"
                          "font: 10pt;");

    QVBoxLayout *layout = new QVBoxLayout;

    layout->setSpacing(0);
    layout->addWidget(header);
    layout->addWidget(view);

    setLayout(layout);
}
