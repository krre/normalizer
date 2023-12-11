#include "ActionBuilder.h"
#include "MainWindow.h"
#include "core/Constants.h"
#include "widget/Menu.h"
#include "dialog/PreferencesDialog.h"
#include "dialog/account/RegisterAccountDialog.h"
#include "dialog/account/LoginDialog.h"
#include "dialog/account/AccountDialog.h"
#include "manager/settings/FileSettings.h"
#include "network/http/HttpNetwork.h"
#include "network/controller/account/UserAccount.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(const Parameters& parameters) :
        QObject(parameters.mainWindow),
        m_mainWindow(parameters.mainWindow),
        m_project(parameters.project),
        m_httpNetwork(parameters.httpNetwork),
        m_fileSettings(parameters.fileSettings) {
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
    accountAction = accountMenu->addAction(tr("Open..."), this, &ActionBuilder::openAccountDialog);
    logoutAction = accountMenu->addAction(tr("Logout"), this, &ActionBuilder::logout);
    updateAccountActions();

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);

    m_httpNetwork->setToken(m_fileSettings->account().token);
}

void ActionBuilder::openPreferencesDialog() {
    PreferencesDialog preferencesDialog(m_fileSettings);
    preferencesDialog.exec();
}

void ActionBuilder::openLoginDialog() {
    Controller::UserAccount account(m_httpNetwork);
    LoginDialog loginDialog(&account);

    if (loginDialog.exec() == QDialog::Accepted) {
        m_fileSettings->setAccount(FileSettings::Account(loginDialog.token()));
        m_httpNetwork->setToken(loginDialog.token());
        updateAccountActions();
    }
}

void ActionBuilder::openAccountDialog() {
    Controller::UserAccount account(m_httpNetwork);
    AccountDialog AccountDialog(&account);

    if (AccountDialog.exec() == QDialog::Accepted && AccountDialog.result() == AccountDialog::Result::Deleted) {
        logout();
    }
}

void ActionBuilder::openRegisterAccountDialog() {
    Controller::UserAccount account(m_httpNetwork);
    RegisterAccountDialog registerAccountDialog(&account);

    if (registerAccountDialog.exec() == QDialog::Accepted) {
        m_fileSettings->setAccount(FileSettings::Account(registerAccountDialog.token()));
        m_httpNetwork->setToken(registerAccountDialog.token());
        updateAccountActions();
    }
}

void ActionBuilder::logout() {
    m_fileSettings->setAccount(FileSettings::Account(""));
    m_httpNetwork->setToken("");
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
    bool tokenExists = !m_fileSettings->account().token.isEmpty();
    registerAction->setVisible(!tokenExists);
    loginAction->setVisible(!tokenExists);
    accountAction->setVisible(tokenExists);
    logoutAction->setVisible(tokenExists);
}
