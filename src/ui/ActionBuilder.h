#pragma once
#include <QObject>

class MainWindow;
class Project;
class HttpNetwork;
class FileSettings;
class RecentMenu;

class QAction;

class ActionBuilder : public QObject {
    Q_OBJECT
public:
    struct Parameters {
        MainWindow* mainWindow;
        Project* project;
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
    void updateAccountActions();

    MainWindow* m_mainWindow = nullptr;
    Project* m_project = nullptr;
    HttpNetwork* m_httpNetwork = nullptr;
    FileSettings* m_fileSettings = nullptr;

    QAction* registerAction = nullptr;
    QAction* loginAction = nullptr;
    QAction* accountAction = nullptr;
    QAction* logoutAction = nullptr;
};
