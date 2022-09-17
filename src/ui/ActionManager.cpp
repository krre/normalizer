#include "ActionManager.h"
#include <QHash>
#include <QAction>

QHash<QString, QAction*> actions;

namespace ActionManager {

void addAction(const QString& id, QAction* action) {
    actions[id] = action;
}

void removeAction(const QString& id) {
    actions.remove(id);
}

QAction* action(const QString& id) {
    return actions.value(id);
}

};
