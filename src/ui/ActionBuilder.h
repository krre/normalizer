#pragma once
#include <QObject>

class MainWindow;
class Project;
class HttpNetwork;
class FileSettingsStorage;
class RecentMenu;

class QAction;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    struct Parameters {
        MainWindow* mainWindow;
        Project* project;
        HttpNetwork* httpNetwork;
        FileSettingsStorage* fileSettingsStorage;
    };

    explicit ActionBuilder(const Parameters& parameters);

private slots:
    void openPreferencesDialog();

    void openLoginDialog();
    void openAccountDialog();
    void openRegisterAccountDialog();
    void logout();

    void about();

private:
    void updateAccountActions();

    MainWindow* m_mainWindow = nullptr;
    Project* m_project = nullptr;
    HttpNetwork* m_httpNetwork = nullptr;
    FileSettingsStorage* m_fileSettingsStorage = nullptr;

    QAction* registerAction = nullptr;
    QAction* loginAction = nullptr;
    QAction* accountAction = nullptr;
    QAction* logoutAction = nullptr;
};
