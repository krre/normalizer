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
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *quitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};
