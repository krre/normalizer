#pragma once
#include <QMainWindow>

class RenderView;
class ActionBuilder;
class Project;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void readSettings();
    void writeSettings();

    RenderView* m_renderView = nullptr;
    ActionBuilder* m_actionBuilder = nullptr;
    Project* m_project = nullptr;
};
