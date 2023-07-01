#pragma once
#include <QObject>

class MainWindow;
class Project;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    explicit ActionBuilder(MainWindow* mainWindow, Project* project);

private slots:
    void newProject();
    void open();
    void save();
    void close();

    void about();

private:
    MainWindow* m_mainWindow = nullptr;
    Project* m_project = nullptr;
};
