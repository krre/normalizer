#pragma once
#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
    class MainWindow;
}

namespace IrbisUnitBuilder {

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
    // File
    void on_actionOpen_triggered();
    void on_actionClose_triggered();
    void on_actionExit_triggered();

    // Unit
    void on_actionAdd_triggered();
    void on_actionRemove_triggered();

    // View
    void on_actionResetView_triggered();

    // Help
    void on_actionAbout_triggered();

private:
    void readSettings();
    void writeSettings();
    void openFile(const QString& filePath);
    void closeFile();
    void changeWindowTitle(const QString& filePath = QString());
    void updateActions();

    QString filePath;
    Ui::MainWindow* ui;
    Settings* settings;
    QScopedPointer<Editor3D> editor3d;
};

} // IrbisUnitBuilder

