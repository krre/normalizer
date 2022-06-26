#pragma once
#include <QMainWindow>

class SourceEditor;

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
    void onOptions();
    void onAbout();

    void onTabClosed(int index);
    void onTabClicked(int index);

    int addSourceTab(const QString& filePath);

private:
    void createActions();
    void createWidgets();

    void readSettings();
    void writeSettings();

    int findSource(const QString& filePath);

    QTabWidget* tabWidget = nullptr;
    SourceEditor* editor = nullptr;
};
