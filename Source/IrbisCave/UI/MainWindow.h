#pragma once
#include <QMainWindow>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class Cave;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_As_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    void readSettings();
    void writeSettings();
    void closeEvent(QCloseEvent* event);

    Ui::MainWindow* ui;
    QSettings settings;
    Cave* cave;
};
