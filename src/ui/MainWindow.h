#pragma once
#include "core/CommonTypes.h"
#include <QMainWindow>
#include <QPropertyNotifier>

class VulkanWindow;
class HttpRestApi;
class FileSettings;
class CodeEditor;
class ActionBuilder;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(VulkanWindow* vulkanWindow);
    ~MainWindow();

public slots:
    void openProject(Id id, const QString& name);
    void closeProject();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void setToRootWidget(QWidget* widget);

    void readSettings();
    void writeSettings();

    VulkanWindow* m_vulkanWindow = nullptr;
    QWidget* m_rootWidget = nullptr;
    QString m_projectName;

    QScopedPointer<HttpRestApi> m_httpRestApi;
    QScopedPointer<FileSettings> m_fileSettings;
    QScopedPointer<CodeEditor> m_codeEditor;

    ActionBuilder* m_actionBuilder = nullptr;
};
