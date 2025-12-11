#pragma once
#include "network/WebSocketClient.h"
#include <QMainWindow>

class Settings;
class Project;
class CodeEditor;
class WebSocketClient;
class NetworkApi;

class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(Settings* settings);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void createProject();
    void openProject();
    void closeProject();

    void showPreferences();
    void showAbout();

    void setConnectionState(WebSocketClient::State state);

private:
    void readSettings();
    void writeSettings();

    void changeWindowTitle();
    void createActions();
    void createCodeEditor();

    void openProjectFromPath(const QString& path);

    Settings* m_settings = nullptr;
    Project* m_project = nullptr;
    CodeEditor* m_codeEditor = nullptr;
    WebSocketClient* m_webSocketClient = nullptr;
    NetworkApi* m_networkApi = nullptr;

    QLabel* m_statusLabel = nullptr;
};
