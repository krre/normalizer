#pragma once
#include <QObject>
#include <QMenuBar>

class MainWindow;

class TopMenu : public QObject {
public:
    TopMenu(MainWindow* mainWindow);
    void updateState();

    void addRecent(const QString& path);
    QMenu* recent() const;

private slots:
    void onNew();
    void onOpen();
    void onClose();
    void onClearRecent();
    void onProjectSettings();
    void onQuit();

    void onAddOperator();

    void onOptions();
    void onAbout();

private:
    bool isProjectActive() const;
    MainWindow* mainWindow = nullptr;
    QMenu* recentMenu = nullptr;
};
