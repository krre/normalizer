#pragma once
#include <QMainWindow>
#include <QPropertyNotifier>

class HttpNetworkManager;
class FileSettingsStorage;
class ProjectTable;
class RenderView;
class ActionBuilder;
class Project;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void readSettings();
    void writeSettings();

    QScopedPointer<HttpNetworkManager> m_httpNetworkManager;
    QScopedPointer<FileSettingsStorage> m_fileSettingsStorage;

    ProjectTable* m_projectTable = nullptr;
    RenderView* m_renderView = nullptr;
    ActionBuilder* m_actionBuilder = nullptr;
    Project* m_project = nullptr;
    QPropertyNotifier m_projectPathNotifier;
};
