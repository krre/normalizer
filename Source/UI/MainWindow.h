#pragma once
#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
    class MainWindow;
}

class Settings;
class Editor3D;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString& filePath = QString());
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    void readSettings();
    void writeSettings();
    void openFile(const QString& filePath);
    void closeFile();
    void changeWindowTitle(const QString& filePath = QString());

    QString m_filePath;
    Ui::MainWindow* ui;
    Settings* settings;
    QScopedPointer<Editor3D> editor3d;
};

