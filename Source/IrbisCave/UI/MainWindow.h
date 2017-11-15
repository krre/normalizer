#pragma once
#include <QMainWindow>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class Cave;
class QTreeView;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();
    void on_actionOptions_triggered();
    void on_actionShow_Left_Sidebar_toggled(bool checked=false);
    void on_actionAbout_triggered();

    void on_tabWidget_editor_tabCloseRequested(int index);

private:
    void readSettings();
    void writeSettings();
    void changeWindowTitle(const QString& filePath = QString());
    void closeEvent(QCloseEvent* event);

    Ui::MainWindow* _ui;
    QSettings _settings;
    QTreeView* _treeView;
    Cave* _currentCave = nullptr;
};
