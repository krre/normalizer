#pragma once
#include <QMainWindow>

class FileSettings;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void readSettings();
    void writeSettings();

    FileSettings* m_fileSettings = nullptr;
};
