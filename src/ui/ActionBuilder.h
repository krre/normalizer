#pragma once
#include <QObject>

class MainWindow;
class Project;
class RecentProjectsMenu;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    explicit ActionBuilder(MainWindow* mainWindow, Project* project);
    RecentProjectsMenu* recentProjectsMenu() const { return m_recentProjectsMenu; }

private slots:
    void newProject();
    void open();

    void about();

private:
    MainWindow* m_mainWindow = nullptr;
    Project* m_project = nullptr;
    RecentProjectsMenu* m_recentProjectsMenu = nullptr;
};
