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
    void onClose();
    void onQuit();
    void onOptions();
    void onAbout();

    void onTabClosed(int index);
    void onTabClicked(int index);

    int addSourceTab(const QString& filePath);

private:
    void createActions();
    void createWidgets();

    void createTabWidget();
    void removeTabWidget();

    void readSettings();
    void writeSettings();

    void readSession();
    void writeSession();

    void openProject(const QString& path);
    void closeProject();
    bool isProjectActive() const;
    int findSource(const QString& filePath);

    void closeWindow();

    QTabWidget* tabWidget = nullptr;
    SourceEditor* editor = nullptr;
    QString projectPath;
};
