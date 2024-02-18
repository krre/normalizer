#pragma once
#include <QObject>

class MainWindow;
class ProjectTable;
class HttpRestApi;
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
        HttpRestApi* httpNetwork;
        FileSettings* fileSettings;
    };

    explicit ActionBuilder(const Parameters& parameters);

    void updateProjectActions();
    void updateAccountActions();

signals:
    void tokenChanged(const QString& token);
    void projectClosed();

private slots:
    void newProject();

    void openPreferencesDialog();

    void openSignInDialog();
    void openAccountDialog();
    void openSignUpDialog();

    void setToken(const QString& token);
    void signOut();

    void about();

private:
    MainWindow* m_mainWindow = nullptr;
    ProjectTable* m_projectTable = nullptr;
    HttpRestApi* m_httpRestApi = nullptr;
    FileSettings* m_fileSettings = nullptr;

    QMenu* m_fileMenu = nullptr;
    QMenu* m_accountMenu = nullptr;

    QAction* m_createProjectAction = nullptr;
    QAction* m_openProjectAction = nullptr;
    QAction* m_closeProjectAction = nullptr;
    QAction* m_editProjectAction = nullptr;
    QAction* m_deleteProjectAction = nullptr;

    QAction* m_signInAction = nullptr;
    QAction* m_signUpAction = nullptr;
    QAction* m_editAccountAction = nullptr;
    QAction* m_accountSeparatorAction = nullptr;
    QAction* m_signOutAction = nullptr;
};
