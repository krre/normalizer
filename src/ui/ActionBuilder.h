#pragma once
#include <QObject>

class MainWindow;
class Project;
class HttpNetworkManager;
class FileSettingsStorage;
class RecentMenu;

class QAction;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    struct Parameters {
        MainWindow* mainWindow;
        Project* project;
        HttpNetworkManager* httpNetworkManager;
        FileSettingsStorage* fileSettingsStorage;
    };

    explicit ActionBuilder(const Parameters& parameters);

private slots:
    void openPreferencesDialog();

    void openLoginDialog();
    void openProfileDialog();
    void openRegisterAccountDialog();
    void logout();

    void about();

private:
    void updateAccountActions();

    MainWindow* m_mainWindow = nullptr;
    Project* m_project = nullptr;
    HttpNetworkManager* m_httpNetworkManager = nullptr;
    FileSettingsStorage* m_fileSettingsStorage = nullptr;

    QAction* registerAction = nullptr;
    QAction* loginAction = nullptr;
    QAction* profileAction = nullptr;
    QAction* logoutAction = nullptr;
};
