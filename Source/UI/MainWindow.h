#pragma once
#include <QMainWindow>
#include <QScopedPointer>

class QProcess;
class QFileSystemModel;

namespace Ui {
    class MainWindow;
}

namespace IrbisCave {

class Cave;
class Settings;
class ProjectTreeView;

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

    // Add
    void on_actionExpression_triggered();
    void on_actionFunction_triggered();
    void on_actionModule_triggered();

    // Build
    void on_actionBuild_triggered();
    void on_actionStop_triggered();

    // Tools
    void on_actionUnitBuilder_triggered();
    void on_actionOptions_triggered();

    // View
    void on_actionShowSidebar_toggled(bool checked=false);
    void on_actionShowOutput_toggled(bool checked=false);
    void on_actionClearOutput_triggered(bool checked=false);

    // Help
    void on_actionAbout_triggered();

    // TabView
    void on_tabWidgetCave_tabCloseRequested(int index);
    void on_tabWidgetCave_currentChanged(int index);

    void onFileDoubleClicked(const QModelIndex& index);
    void onFileRemoved(const QString& filePath);

    void addCaveTab(const QString& filePath);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void readSettings();
    void writeSettings();
    void saveSession();
    void restoreSession();
    void changeWindowTitle(const QString& filePath = QString());
    void openProject(const QString& filePath);
    void closeProject();
    int findCave(const QString& filePath);

    Ui::MainWindow* ui;
    Settings* settings;
    ProjectTreeView* projectTreeView;
    QScopedPointer<QFileSystemModel> fsModel;
    QProcess* process;
    QString projectPath;
};

} // IrbisCave
