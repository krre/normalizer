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
    void onClearRecent();
    void onProjectSettings();
    void onQuit();

    void onAddOperator();

    void onOptions();
    void onAbout();

private:
    void createActions();
    void createWidgets();

    void createSourceEditor();
    void removeSourceEditor();

    void readSettings();
    void writeSettings();

    void readSession();
    void writeSession();

    void addRecent(const QString& path);
    void updateMenuState();

    void openProject(const QString& path);
    void closeProject();
    bool isProjectActive() const;

    void closeWindow();

    QMenu* recentMenu = nullptr;
    SourceEditor* sourceEditor = nullptr;
};
