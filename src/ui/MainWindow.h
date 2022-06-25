#pragma once
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onNew();
    void onOpen();
    void onQuit();
    void onAbout();

private:
    void createActions();

    void readSettings();
    void writeSettings();
};
