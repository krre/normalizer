#pragma once
#include "WorkArea.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QSplitter>
#include <QFileSystemModel>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);

protected:
    void closeEvent(QCloseEvent* event) override;
    void timerEvent(QTimerEvent*);

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
    void readSettings();
    void writeSettings();
    bool maybeSave();

    WorkArea* workArea;
    QSplitter* splitter;
    QFileSystemModel* fileSystemModel;
    int timerId;
};
