#pragma once
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& filePath = QString());
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    void openFile(const QString& filePath);
    void changeWindowTitle(const QString& filePath = QString());

    QString _filePath;
    Ui::MainWindow* _ui;
};

