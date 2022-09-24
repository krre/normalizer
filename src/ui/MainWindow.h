#pragma once
#include <QMainWindow>

class SourceEditor;
class TopMenu;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void openProject(const QString& path);
    void closeProject();

    void closeWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void createSourceEditor();
    void removeSourceEditor();

    void readSettings();
    void writeSettings();

    void readSession();
    void writeSession();

    bool isProjectActive() const;

    TopMenu* topMenu = nullptr;
    SourceEditor* sourceEditor = nullptr;
};
