#pragma once
#include <QObject>

class MainWindow;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    explicit ActionBuilder(MainWindow* mainWindow);

private slots:
    void about();

private:
    MainWindow* m_mainWindow = nullptr;
};
