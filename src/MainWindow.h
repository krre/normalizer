#pragma once
#include <QMainWindow>

class RenderView;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void about();

private:
    void readSettings();
    void writeSettings();

    void createActions();

    RenderView* m_renderView = nullptr;
};
