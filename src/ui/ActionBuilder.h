#pragma once
#include <QObject>

class MainWindow;
class Project;
class RecentMenu;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    explicit ActionBuilder(MainWindow* mainWindow, Project* project);
    RecentMenu* recentProjectsMenu() const { return m_recentProjectsMenu; }

private slots:
    void open();
    void showPreferences();
    void about();

private:
    MainWindow* m_mainWindow = nullptr;
    Project* m_project = nullptr;
    RecentMenu* m_recentProjectsMenu = nullptr;
};
