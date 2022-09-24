#pragma once

class QAction;
class QString;

namespace ActionManager {
    constexpr auto NewProject = "NewProject";
    constexpr auto OpenProject = "OpenProject";
    constexpr auto CloseProject = "CloseProject";
    constexpr auto ProjectSettings = "ProjectSettings";
    constexpr auto Exit = "Exit";

    constexpr auto AddOperator = "AddOperator";

    void addAction(const QString& id, QAction* action);
    void removeAction(const QString& id);
    QAction* action(const QString& id);
};
