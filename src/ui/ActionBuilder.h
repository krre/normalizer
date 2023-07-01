#pragma once
#include <QObject>

class MainWindow;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    explicit ActionBuilder(MainWindow* mainWindow);

private slots:
    void newFile();
    void open();
    void save();
    void close();

    void about();

private:
    MainWindow* m_mainWindow = nullptr;
};
