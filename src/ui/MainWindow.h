#pragma once
#include "core/CommonTypes.h"
#include <QMainWindow>
#include <QPropertyNotifier>

class HttpRestApi;
class FileSettings;
class CodeEditor;
class ActionBuilder;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
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

    QWidget* m_rootWidget = nullptr;

    QScopedPointer<HttpRestApi> m_httpRestApi;
    QScopedPointer<FileSettings> m_fileSettings;
    QScopedPointer<CodeEditor> m_codeEditor;

    ActionBuilder* m_actionBuilder = nullptr;
};
