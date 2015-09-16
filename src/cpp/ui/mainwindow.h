#pragma once
#include <QMainWindow>

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void newFile();
    void open();
    void quitApp();
    void about();
    void aboutQt();

private:
    void createMenus();
    void closeEvent(QCloseEvent* event) override;
    void saveSettings();
    void loadSettings();

    QMenu *fileMenu;
    QMenu *helpMenu;
};
