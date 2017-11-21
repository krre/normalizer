#pragma once
#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
    class MainWindow;
}

class Editor3D;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString& filePath = QString());
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    void openFile(const QString& filePath);
    void closeFile();
    void changeWindowTitle(const QString& filePath = QString());

    QString _filePath;
    Ui::MainWindow* _ui;
    QScopedPointer<Editor3D> editor3d;
};

