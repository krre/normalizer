#pragma once
#include <QMainWindow>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    void readSettings();
    void writeSettings();

    Ui::MainWindow* ui;
    QSettings settings;
};
