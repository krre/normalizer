#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class Cave;
class Settings;
class QTreeView;
class QFileSystemModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSaveAs_triggered();
    void on_actionClose_triggered();
    void on_actionCloseAll_triggered();
    void on_actionCloseOther_triggered();
    void on_actionExit_triggered();
    void on_actionOptions_triggered();
    void on_actionShowSidebar_toggled(bool checked=false);
    void on_actionAbout_triggered();

    void on_tabWidgetCave_tabCloseRequested(int index);
    void on_tabWidgetCave_currentChanged(int index);

    void onFileDoubleClicked(const QModelIndex& index);

private:
    void readSettings();
    void writeSettings();
    void changeWindowTitle(const QString& filePath = QString());
    void addCaveTab(const QString& filePath);
    int findCave(const QString& filePath);
    void closeEvent(QCloseEvent* event);

    Ui::MainWindow* _ui;
    Settings* _settings;
    QTreeView* _treeView;
    QFileSystemModel* _fsModel;
    Cave* _currentCave = nullptr;
};
