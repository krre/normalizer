#include "ActionBuilder.h"
#include "MainWindow.h"
#include "core/Constants.h"
#include "widget/Menu.h"
#include "dialog/PreferencesDialog.h"
#include "dialog/account/RegisterAccountDialog.h"
#include "dialog/account/LoginDialog.h"
#include "dialog/account/ProfileDialog.h"
#include "manager/settings/FileSettingsStorage.h"
#include "network/http/HttpNetworkManager.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(const Parameters& parameters) :
        QObject(parameters.mainWindow),
        m_mainWindow(parameters.mainWindow),
        m_project(parameters.project),
        m_httpNetworkManager(parameters.httpNetworkManager),
        m_fileSettingsStorage(parameters.fileSettingsStorage) {
    QMenuBar* menuBar = m_mainWindow->menuBar();

    auto fileMenu = new Menu(tr("File"), menuBar);
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, m_mainWindow, &MainWindow::close);

    auto editMenu = new Menu(tr("Edit"), menuBar);
    menuBar->addMenu(editMenu);

    editMenu->addAction(tr("Preferences..."), this, &ActionBuilder::openPreferencesDialog);

    auto accountMenu = menuBar->addMenu(tr("Account"));
    registerAction = accountMenu->addAction(tr("Register..."), this, &ActionBuilder::openRegisterAccountDialog);
    loginAction = accountMenu->addAction(tr("Login..."), this, &ActionBuilder::openLoginDialog);
    profileAction = accountMenu->addAction(tr("Profile..."), this, &ActionBuilder::openProfileDialog);
    logoutAction = accountMenu->addAction(tr("Logout"), this, &ActionBuilder::logout);
    updateAccountActions();

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);

    m_httpNetworkManager->setToken(m_fileSettingsStorage->account().token);
}

void ActionBuilder::openPreferencesDialog() {
    PreferencesDialog preferencesDialog(m_fileSettingsStorage);
    preferencesDialog.exec();
}

void ActionBuilder::openLoginDialog() {
    LoginDialog loginDialog(m_httpNetworkManager);

    if (loginDialog.exec() == QDialog::Accepted) {
        m_fileSettingsStorage->setAccount(FileSettingsStorage::Account(loginDialog.token()));
        m_httpNetworkManager->setToken(loginDialog.token());
        updateAccountActions();
    }
}

void ActionBuilder::openProfileDialog() {
    ProfileDialog profileDialog(m_httpNetworkManager);

    if (profileDialog.exec() == QDialog::Accepted && profileDialog.result() == ProfileDialog::Result::Deleted) {
        logout();
    }
}

void ActionBuilder::openRegisterAccountDialog() {
    RegisterAccountDialog registerAccountDialog(m_httpNetworkManager);

    if (registerAccountDialog.exec() == QDialog::Accepted) {
        m_fileSettingsStorage->setAccount(FileSettingsStorage::Account(registerAccountDialog.token()));
        m_httpNetworkManager->setToken(registerAccountDialog.token());
        updateAccountActions();
    }
}

void ActionBuilder::logout() {
    m_fileSettingsStorage->setAccount(FileSettingsStorage::Account(""));
    m_httpNetworkManager->setToken("");
    updateAccountActions();
}

void ActionBuilder::about() {
    using namespace Const::App;

    QMessageBox::about(m_mainWindow, tr("About %1").arg(Name),
        tr("<h3>%1 %2</h3>"
          "Cloud IDE for the Norm visual programming language<br><br>"
          "Based on Qt %3<br>"
          "Build on %4 %5<br><br>"
          "<a href=%6>%6</a><br><br>Copyright © %7, Vladimir Zarypov")
              .arg(Name, Version, QT_VERSION_STR, BuildDate, BuildTime, URL, CopyrightYear));
}

void ActionBuilder::updateAccountActions() {
    bool tokenExists = !m_fileSettingsStorage->account().token.isEmpty();
    registerAction->setVisible(!tokenExists);
    loginAction->setVisible(!tokenExists);
    profileAction->setVisible(tokenExists);
    logoutAction->setVisible(tokenExists);
}
