#pragma once
#include <QMainWindow>
#include <QPropertyNotifier>

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

private:
    void readSettings();
    void writeSettings();

    QScopedPointer<HttpNetwork> m_httpNetwork;
    QScopedPointer<FileSettings> m_fileSettings;

    ProjectTable* m_projectTable = nullptr;
    RenderView* m_renderView = nullptr;
    ActionBuilder* m_actionBuilder = nullptr;
    QPropertyNotifier m_projectPathNotifier;
};
