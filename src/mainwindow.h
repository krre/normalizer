#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "commandline.h"
#include "visualarea.h"

class QAction;
class QMenu;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow();

private slots:
    void newFile();
    void open();
    void save();
    void quitApp();
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();

    VisualArea visualArea;
    CommandLine commandLine;

    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *quitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif // MAINWINDOW_H
