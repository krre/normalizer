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

    void onUndo();
    void onRedo();

    void onAddOperator();
    void onAddExpression();

    void onBuild();
    void onRun();

    void onPreferences();
    void onAbout();

private:
    bool isProjectActive() const;
    MainWindow* mainWindow = nullptr;
    QMenu* recentMenu = nullptr;
    QMenu* editMenu = nullptr;
    QMenu* unitMenu = nullptr;
    QMenu* addMenu = nullptr;
    QMenu* buildMenu = nullptr;
};
