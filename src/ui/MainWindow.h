#pragma once
#include "core/CommonTypes.h"
#include <QMainWindow>
#include <QPropertyNotifier>

namespace Controller {
    class NormProject;
}

class HttpRestApi;
class FileSettings;
class ProjectTable;
class CodeEditor;
class ActionBuilder;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void openProject(Id id, const QString& name);
    void closeProject();

private:
    void setToRootWidget(QWidget* widget);

    void readSettings();
    void writeSettings();

    QWidget* m_rootWidget = nullptr;

    QScopedPointer<HttpRestApi> m_httpNetwork;
    QScopedPointer<FileSettings> m_fileSettings;
    QScopedPointer<Controller::NormProject> m_project;

    QScopedPointer<ProjectTable> m_projectTable;
    QScopedPointer<CodeEditor> m_codeEditor;

    ActionBuilder* m_actionBuilder = nullptr;
};
