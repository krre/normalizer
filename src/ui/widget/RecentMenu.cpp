#include "RecentMenu.h"
#include <QDir>

constexpr auto systemActionCount = 2;
constexpr auto maxRecentFiles = 10;

RecentMenu::RecentMenu(const QString& title, QWidget* parent) : QMenu(title, parent) {
    addSeparator();
    addAction(tr("Clear"), this, &RecentMenu::clear);
}

void RecentMenu::clear() {
    for (int i = actions().size() - systemActionCount - 1; i >= 0; i--) {
        removeAction(actions().at(i));
    }
}

void RecentMenu::addPath(const QString& path) {
    if (path.isEmpty()) return;

    QDir dir(path);
    if (!dir.exists()) return;

    for (QAction* action : actions()) {
        if (action->text() == path) {
            removeAction(action);
        }
    }

    auto pathAction = new QAction(path);
    connect(pathAction, &QAction::triggered, this, [=, this] {
        emit activated(path);
    });

    insertAction(actions().constFirst(), pathAction);

    if (actions().size() > maxRecentFiles + systemActionCount) {
        removeAction(actions().at(actions().size() - systemActionCount - 1));
    }
}

QStringList RecentMenu::pathes() const {
    QStringList result;

    for (int i = 0; i < actions().size() - systemActionCount; ++i) {
        result.append(actions().at(i)->text());
    }

    return result;
}

void RecentMenu::setPathes(const QStringList& pathes) {
    for (const QString& path : pathes) {
        addPath(path);
    }
}
