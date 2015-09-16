#pragma once
#include <QMainWindow>

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

public:
    void addTab(const QString& name, const QString& path);

private slots:
    void onNewTab();
    void open();
    void quitApp();
    void about();
    void aboutQt();
    void onCloseTab(int index);
    void onCloseCurrentTab();
    void onCloseAllTabs();
    void onCloseOthersTabs();
    void onActiveTabChanged(int index);

private:
    void createMenus();
    void setupTabWidget();
    void closeEvent(QCloseEvent* event) override;
    void saveSettings();
    void loadSettings();

    QMenu *fileMenu;
    QMenu *helpMenu;
    QTabWidget tabWidget;
};
