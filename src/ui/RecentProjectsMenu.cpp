#include "RecentProjectsMenu.h"
#include "core/Settings.h"
#include <QDir>

constexpr auto systemActionCount = 2;
constexpr auto maxRecentFiles = 10;


RecentProjectsMenu::RecentProjectsMenu(const QString& title, QWidget* parent) : QMenu(title, parent) {
    addSeparator();
    addAction(tr("Clear"), this, &RecentProjectsMenu::clear);

    for (const QString& path : Settings::value<General::RecentProjects>()) {
        addPath(path);
    }
}

RecentProjectsMenu::~RecentProjectsMenu() {
    QStringList pathes;

    for (int i = 0; i < actions().size() - systemActionCount; ++i) {
        pathes.append(actions().at(i)->text());
    }

    Settings::setValue<General::RecentProjects>(pathes);
}

void RecentProjectsMenu::clear() {
    for (int i = actions().size() - systemActionCount - 1; i >= 0; i--) {
        removeAction(actions().at(i));
    }
}

void RecentProjectsMenu::addPath(const QString& path) {
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
