#pragma once
#include <QObject>

class MainWindow;
class ProjectTable;
class HttpNetwork;
class FileSettings;
class RecentMenu;

class QMenu;
class QAction;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    struct Parameters {
        MainWindow* mainWindow;
        ProjectTable* projectTable;
        HttpNetwork* httpNetwork;
        FileSettings* fileSettings;
    };

    explicit ActionBuilder(const Parameters& parameters);

signals:
    void loggedChanged(bool logged);
    void projectClosed();

private slots:
    void openPreferencesDialog();

    void openLoginDialog();
    void openAccountDialog();
    void openRegisterAccountDialog();

    void login(const QString& token);
    void logout();

    void about();

private:
    void updateProjectActions();
    void updateAccountActions();

    MainWindow* m_mainWindow = nullptr;
    ProjectTable* m_projectTable = nullptr;
    HttpNetwork* m_httpNetwork = nullptr;
    FileSettings* m_fileSettings = nullptr;

    QMenu* m_projectMenu = nullptr;

    QAction* m_addProjectAction = nullptr;
    QAction* m_openProjectAction = nullptr;
    QAction* m_closeProjectAction = nullptr;
    QAction* m_editProjectAction = nullptr;
    QAction* m_deleteProjectAction = nullptr;

    QAction* m_registerAction = nullptr;
    QAction* m_loginAction = nullptr;
    QAction* m_accountAction = nullptr;
    QAction* m_logoutAction = nullptr;
};
