#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void on_actionExit_triggered(bool checked=false);
    void on_actionAbout_triggered(bool checked=false);

private:
    Ui::MainWindow* ui;
};
