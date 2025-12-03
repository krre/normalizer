#pragma once
#include <QMainWindow>

class FileSettings;
class Project;
class CodeEditor;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void createProject();
    void openProject();
    void closeProject();

    void showPreferences();
    void showAbout();

private:
    void readSettings();
    void writeSettings();

    void changeWindowTitle();
    void createActions();
    void createCodeEditor();

    FileSettings* m_fileSettings = nullptr;
    Project* m_project = nullptr;
    CodeEditor* m_codeEditor = nullptr;
};
