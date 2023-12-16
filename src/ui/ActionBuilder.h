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
    QAction* m_editProjectAction = nullptr;
    QAction* m_deleteProjectAction = nullptr;

    QAction* registerAction = nullptr;
    QAction* loginAction = nullptr;
    QAction* accountAction = nullptr;
    QAction* logoutAction = nullptr;
};
