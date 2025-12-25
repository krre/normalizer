#pragma once
#include "network/Network.h"
#include "core/async/Task.h"
#include <QMainWindow>

class Settings;
class Project;
class CodeEditor;
class Network;

class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(Settings* settings);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void createWorkspace();
    void createProject();
    void closeProject();

    void showPreferences();
    void showAbout();

    void setConnectionState(Network::State state);

private:
    void readSettings();
    void writeSettings();

    void changeWindowTitle();
    void createActions();
    void createCodeEditor();

    void openProjectFromPath(const QString& path);

    Async::Task<void> onConnected();
    void onDisconnected();

    Settings* m_settings = nullptr;
    Project* m_project = nullptr;
    CodeEditor* m_codeEditor = nullptr;
    Network* m_network = nullptr;

    QLabel* m_statusLabel = nullptr;
};
