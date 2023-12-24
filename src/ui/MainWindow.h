#pragma once
#include "core/CommonTypes.h"
#include <QMainWindow>
#include <QPropertyNotifier>

namespace Controller {
    class NormProject;
}

class HttpNetwork;
class FileSettings;
class ProjectTable;
class RenderView;
class ActionBuilder;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void openProject(Id id);
    void closeProject();

private:
    void setToRootWidget(QWidget* widget);

    void readSettings();
    void writeSettings();

    QWidget* m_rootWidget = nullptr;

    QScopedPointer<HttpNetwork> m_httpNetwork;
    QScopedPointer<FileSettings> m_fileSettings;
    QScopedPointer<Controller::NormProject> m_project;

    QScopedPointer<ProjectTable> m_projectTable;
    QScopedPointer<RenderView> m_renderView;

    ActionBuilder* m_actionBuilder = nullptr;
};
