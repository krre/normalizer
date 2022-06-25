#pragma once
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNew();
    void onOpen();
    void onQuit();
    void onAbout();

    void onTabClosed(int index);
    void onTabClicked(int index);

private:
    void createActions();
    void createWidgets();

    void readSettings();
    void writeSettings();

    QTabWidget* tabWidget = nullptr;
};
