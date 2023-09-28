#include "ProjectTable.h"

ProjectTable::ProjectTable() {
    setColumnCount(5);
    setHorizontalHeaderLabels({ tr("Name"), tr("Templace"), tr("Description"), tr("Created time"), tr("Updated time") });
    setSelectionBehavior(QAbstractItemView::SelectItems);
}
