#pragma once
#include <QMainWindow>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class Editor3D;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionClose_All_triggered();
    void on_actionClose_Other_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionShow_left_sidebar_toggled(bool checked=false);
    void on_actionBuild_triggered();
    void on_actionOptions_triggered();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow* ui;
    QSettings settings;
    Editor3D* currentEditor3D = nullptr;

    void readSettings();
    void writeSettings();
    void toggleMenusVisible(bool visible);
    void toggleActionEnable(bool enable);
    void tabCountChanged(int count);
    void createEditor3D(const QString& filePath, bool isNew);
};
