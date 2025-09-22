#pragma once
#include <QMainWindow>

class FileSettings;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void createActions();

    FileSettings* m_fileSettings = nullptr;
};
