#pragma once
#include <QMainWindow>
#include <QAction>
#include "workarea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void quitApp();
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();

    WorkArea workArea;

    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* quitAct;
    QAction* aboutAct;
    QAction* aboutQtAct;
};
