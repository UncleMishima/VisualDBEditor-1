#include "TablesDrawingArea.h"

#include <QPainter>

#include "TableView.h"
#include "Relation.h"

TablesDrawingArea::TablesDrawingArea(QWidget *parent): QWidget(parent)
{

}

void TablesDrawingArea::paintEvent(QPaintEvent *)
{
    if (!isShowRelations || relations == nullptr)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    Q_ASSERT_X(displayMode != nullptr, "paintEvent", "displayMode = nullptr");
    Q_ASSERT_X(tableViews != nullptr, "paintEvent", "tableViews = nullptr");
    switch (*displayMode)
    {
        case CLASSES:
        {
            foreach (Relation *relation, *relations)
            {
                TableView *table1 = tableViews->at(relation->getTableId(0));
                TableView *table2 = tableViews->at(relation->getTableId(1));

                painter.drawLine(table1->geometry().center(),
                                 table2->geometry().center());
            }
        }

        default:
            return;
    }
}

