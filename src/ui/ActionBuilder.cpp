#include "ActionBuilder.h"
#include "MainWindow.h"
#include "core/Application.h"
#include "widget/Menu.h"
#include "widget/project/ProjectTable.h"
#include "dialog/project/NewProjectDialog.h"
#include "dialog/PreferencesDialog.h"
#include "dialog/account/SignUpDialog.h"
#include "dialog/account/SignInDialog.h"
#include "dialog/account/AccountDialog.h"
#include "external/settings/FileSettings.h"
#include "external/process/NormProcess.h"
#include "external/repository/network/http/HttpRestApi.h"
#include "external/repository/network/controller/account/Account.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(const Parameters& parameters) :
        QObject(parameters.mainWindow),
        m_mainWindow(parameters.mainWindow),
        m_httpRestApi(parameters.httpNetwork),
        m_fileSettings(parameters.fileSettings) {
    QMenuBar* menuBar = m_mainWindow->menuBar();

    m_fileMenu = menuBar->addMenu(tr("File"));
    m_fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &ActionBuilder::newProject);
    m_fileMenu->addSeparator();
    m_closeAction = m_fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, m_mainWindow, &MainWindow::closeProject);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, m_mainWindow, &MainWindow::close);

    auto editMenu = new Menu(tr("Edit"), menuBar);
    menuBar->addMenu(editMenu);

    editMenu->addAction(tr("Preferences..."), this, &ActionBuilder::openPreferencesDialog);

    m_accountMenu = menuBar->addMenu(tr("Account"));
    m_signInAction = m_accountMenu->addAction(tr("Sign In..."), this, &ActionBuilder::openSignInDialog);
    m_signUpAction = m_accountMenu->addAction(tr("Sign Up..."), this, &ActionBuilder::openSignUpDialog);
    m_projectsAction = m_accountMenu->addAction(tr("Projects..."), this, &ActionBuilder::openProjectsTable);
    m_editAccountAction = m_accountMenu->addAction(tr("Edit..."), this, &ActionBuilder::openAccountDialog);
    m_accountSeparatorAction = m_accountMenu->addSeparator();
    m_signOutAction = m_accountMenu->addAction(tr("Sign Out"), this, &ActionBuilder::signOut);

    updateFileActions(false);
    updateAccountActions();

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &ActionBuilder::about);

    m_httpRestApi->setToken(m_fileSettings->account().token);
}

void ActionBuilder::updateFileActions(bool isProjectOpen) {
    m_closeAction->setEnabled(isProjectOpen);
}

void ActionBuilder::updateAccountActions() {
    bool tokenExists = !m_fileSettings->account().token.isEmpty();
    m_signInAction->setVisible(!tokenExists);
    m_signUpAction->setVisible(!tokenExists);
    m_projectsAction->setVisible(tokenExists);
    m_editAccountAction->setVisible(tokenExists);
    m_accountSeparatorAction->setVisible(tokenExists);
    m_signOutAction->setVisible(tokenExists);
}

void ActionBuilder::openPreferencesDialog() {
    PreferencesDialog preferencesDialog(m_fileSettings);

    if (preferencesDialog.exec() == QDialog::Accepted) {
        m_httpRestApi->setUrl(m_fileSettings->projectLocation().host);
    }
}

void ActionBuilder::openSignInDialog() {
    Controller::Account account(m_httpRestApi);
    SingInDialog signInDialog(&account);

    if (signInDialog.exec() == QDialog::Accepted) {
        setToken(signInDialog.token());
    }
}

void ActionBuilder::openAccountDialog() {
    Controller::Account account(m_httpRestApi);
    AccountDialog AccountDialog(&account);

    if (AccountDialog.exec() == QDialog::Accepted && AccountDialog.result() == AccountDialog::Result::Deleted) {
        setToken(QString());
    }
}

void ActionBuilder::openSignUpDialog() {
    Controller::Account account(m_httpRestApi);
    SignUpDialog signUpDialog(&account);

    if (signUpDialog.exec() == QDialog::Accepted) {
        setToken(signUpDialog.token());
    }
}

void ActionBuilder::openProjectsTable() {
    auto projectTable = new ProjectTable(m_httpRestApi, m_fileSettings);
    connect(projectTable, &ProjectTable::openClicked, m_mainWindow, &MainWindow::openProject);
    projectTable->show();
}

void ActionBuilder::setToken(const QString& token) {
    m_fileSettings->setAccount(FileSettings::Account(token));
    m_httpRestApi->setToken(token);
    updateAccountActions();
    emit tokenChanged(token);
}

void ActionBuilder::signOut() {
    setToken(QString());
}

void ActionBuilder::about() {
    QMessageBox::about(m_mainWindow, Application::Name,
        tr("<h3>%1 %2</h3>"
          "Cloud IDE for the Norm visual programming language<br><br>"
          "Based on Qt %3<br>"
          "Build on %4 %5<br><br>"
          "<a href=%6>%6</a><br><br>Copyright © %7, Vladimir Zarypov")
                           .arg(Application::Name, Application::Version, QT_VERSION_STR,
                            Application::BuildDate, Application::BuildTime, Application::Url, Application::CopyrightYear));
}

void ActionBuilder::newProject() {
    NormProcess process(m_fileSettings);

    NewProjectDialog newProjectDialog(&process, m_fileSettings);
    newProjectDialog.exec();
}
