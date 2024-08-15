#include "TableWidget.h"
#include <QHeaderView>
#include <QMouseEvent>

TableWidget::TableWidget() {
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFocusPolicy(Qt::NoFocus);
    horizontalHeader()->setHighlightSections(false);
    verticalHeader()->setVisible(false);
}

void TableWidget::mousePressEvent(QMouseEvent* event) {
    if (!indexAt(event->pos()).isValid()) {
        return;
    }

    QTableView::mousePressEvent(event);
}
