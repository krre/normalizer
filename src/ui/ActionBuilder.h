#pragma once
#include <QObject>

class MainWindow;
class Project;
class RecentMenu;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    explicit ActionBuilder(MainWindow* mainWindow, Project* project);

private slots:
    void openPreferencesDialog();
    void logout();
    void about();

private:
    MainWindow* m_mainWindow = nullptr;
    Project* m_project = nullptr;
};
