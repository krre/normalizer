#include "ActionBuilder.h"
#include "MainWindow.h"
#include "core/Constants.h"
#include "widget/Menu.h"
#include "widget/project/ProjectTable.h"
#include "dialog/PreferencesDialog.h"
#include "dialog/account/RegisterAccountDialog.h"
#include "dialog/account/LoginDialog.h"
#include "dialog/account/AccountDialog.h"
#include "settings/FileSettings.h"
#include "network/http/HttpNetwork.h"
#include "network/controller/account/UserAccount.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(const Parameters& parameters) :
        QObject(parameters.mainWindow),
        m_mainWindow(parameters.mainWindow),
        m_projectTable(parameters.projectTable),
        m_httpNetwork(parameters.httpNetwork),
        m_fileSettings(parameters.fileSettings) {
    QMenuBar* menuBar = m_mainWindow->menuBar();

    auto fileMenu = new Menu(tr("File"), menuBar);
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, m_mainWindow, &MainWindow::close);

    auto editMenu = new Menu(tr("Edit"), menuBar);
    menuBar->addMenu(editMenu);

    editMenu->addAction(tr("Preferences..."), this, &ActionBuilder::openPreferencesDialog);

    m_projectMenu = menuBar->addMenu(tr("Project"));
    m_projectMenu->menuAction()->setVisible(!m_fileSettings->account().token.isEmpty());
    m_addProjectAction = m_projectMenu->addAction(tr("Add..."), m_projectTable, &ProjectTable::add);
    m_editProjectAction = m_projectMenu->addAction(tr("Edit..."), m_projectTable, &ProjectTable::edit);
    m_deleteProjectAction = m_projectMenu->addAction(tr("Delete..."), m_projectTable, &ProjectTable::deleteProject);
    connect(m_projectTable, &ProjectTable::currentRowChanged, this, &ActionBuilder::updateProjectActions);
    updateProjectActions();

    auto accountMenu = menuBar->addMenu(tr("Account"));
    m_registerAction = accountMenu->addAction(tr("Register..."), this, &ActionBuilder::openRegisterAccountDialog);
    m_loginAction = accountMenu->addAction(tr("Login..."), this, &ActionBuilder::openLoginDialog);
    m_accountAction = accountMenu->addAction(tr("Edit..."), this, &ActionBuilder::openAccountDialog);
    m_logoutAction = accountMenu->addAction(tr("Logout"), this, &ActionBuilder::logout);
    updateAccountActions();

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);

    m_httpNetwork->setToken(m_fileSettings->account().token);
}

void ActionBuilder::openPreferencesDialog() {
    PreferencesDialog preferencesDialog(m_fileSettings);

    if (preferencesDialog.exec() == QDialog::Accepted) {
        m_httpNetwork->setUrl(m_fileSettings->server().url);
    }
}

void ActionBuilder::openLoginDialog() {
    Controller::UserAccount account(m_httpNetwork);
    LoginDialog loginDialog(&account);

    if (loginDialog.exec() == QDialog::Accepted) {
        login(loginDialog.token());
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
        login(registerAccountDialog.token());
    }
}

void ActionBuilder::login(const QString& token) {
    m_fileSettings->setAccount(FileSettings::Account(token));
    m_httpNetwork->setToken(token);
    m_projectMenu->menuAction()->setVisible(true);
    updateAccountActions();
    updateProjectActions();
    emit loggedChanged(true);
}

void ActionBuilder::logout() {
    m_fileSettings->setAccount(FileSettings::Account(""));
    m_httpNetwork->setToken("");
    m_projectMenu->menuAction()->setVisible(false);
    updateAccountActions();
    emit loggedChanged(false);
}

void ActionBuilder::about() {
    using namespace Const::App;

    QMessageBox::about(m_mainWindow, Name,
        tr("<h3>%1 %2</h3>"
          "Cloud IDE for the Norm visual programming language<br><br>"
          "Based on Qt %3<br>"
          "Build on %4 %5<br><br>"
          "<a href=%6>%6</a><br><br>Copyright © %7, Vladimir Zarypov")
                           .arg(Name, Version, QT_VERSION_STR, BuildDate, BuildTime, URL, CopyrightYear));
}

void ActionBuilder::updateProjectActions() {
    m_editProjectAction->setEnabled(m_projectTable->isActive());
    m_deleteProjectAction->setEnabled(m_projectTable->isActive());
}

void ActionBuilder::updateAccountActions() {
    bool tokenExists = !m_fileSettings->account().token.isEmpty();
    m_registerAction->setVisible(!tokenExists);
    m_loginAction->setVisible(!tokenExists);
    m_accountAction->setVisible(tokenExists);
    m_logoutAction->setVisible(tokenExists);
}
