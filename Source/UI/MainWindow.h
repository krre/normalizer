#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class Cave;
class Settings;
class QTreeView;
class QFileSystemModel;
class QProcess;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    // File
    void on_actionNewProject_triggered();
    void on_actionNewIrbis_triggered();
    void on_actionOpenProject_triggered();
    void on_actionOpenFile_triggered();
    void on_actionSaveFileAs_triggered();
    void on_actionCloseProject_triggered();
    void on_actionClose_triggered();
    void on_actionCloseAll_triggered();
    void on_actionCloseOther_triggered();
    void on_actionExit_triggered();

    // Build
    void on_actionBuild_triggered();
    void on_actionStop_triggered();

    // Tools
    void on_actionUnitBuilder_triggered();
    void on_actionOptions_triggered();

    // View
    void on_actionShowSidebar_toggled(bool checked=false);

    // Help
    void on_actionAbout_triggered();

    // TabView
    void on_tabWidgetCave_tabCloseRequested(int index);
    void on_tabWidgetCave_currentChanged(int index);

    void onFileDoubleClicked(const QModelIndex& index);

private:
    void readSettings();
    void writeSettings();
    void saveSession();
    void restoreSession();
    void changeWindowTitle(const QString& filePath = QString());
    void changeProject(const QString& projectPath = QString());
    void addCaveTab(const QString& filePath);
    int findCave(const QString& filePath);
    void closeEvent(QCloseEvent* event);

    Ui::MainWindow* _ui;
    Settings* _settings;
    QTreeView* _projectTreeView;
    QFileSystemModel* _fsModel;
    QProcess* _process;
    QString _projectPath;
};
