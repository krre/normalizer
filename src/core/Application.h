#pragma once
#include <QApplication>

class MainWindow;

class Application : public QApplication {
public:
    Application(int& argc, char* argv[]);
    void setMainWindow(MainWindow* mainWindow);

    bool notify(QObject* receiver, QEvent* event) override;

private:
    MainWindow* m_mainWindow = nullptr;
};
