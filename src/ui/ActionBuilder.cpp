#include "ActionBuilder.h"
#include "MainWindow.h"
#include "project/Project.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "widget/Menu.h"
#include "widget/Action.h"
#include "dialog/PreferencesDialog.h"
#include "dialog/account/RegisterAccountDialog.h"
#include "manager/settings/SettingsManager.h"
#include "manager/network/HttpNetworkManager.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(MainWindow* mainWindow, Project* project) : QObject(mainWindow),
        m_mainWindow(mainWindow), m_project(project) {
    QMenuBar* menuBar = mainWindow->menuBar();

    auto fileMenu = new Menu(tr("File"), menuBar);
    menuBar->addMenu(fileMenu);

    fileMenu->addBindableAction(tr("Close"), Qt::CTRL | Qt::Key_W, project, &Project::close)->enabled().setBinding([this] { return m_project->opened().value(); });
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, mainWindow, &MainWindow::close);

    auto editMenu = new Menu(tr("Edit"), menuBar);
    menuBar->addMenu(editMenu);

    editMenu->addAction(tr("Preferences..."), this, &ActionBuilder::openPreferencesDialog);

    auto accountMenu = menuBar->addMenu(tr("Account"));
    accountMenu->addAction(tr("Register"), this, &ActionBuilder::openRegisterAccountDialog);
    accountMenu->addAction(tr("Logout"), this, &ActionBuilder::logout);

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);
}

void ActionBuilder::openPreferencesDialog() {
    SettingsManager settingsManager;

    PreferencesDialog preferencesDialog(&settingsManager);
    preferencesDialog.exec();
}

void ActionBuilder::openRegisterAccountDialog() {
    SettingsManager settingsManager;
    HttpNetworkManager networkManager(settingsManager.serverAddress().host, settingsManager.serverAddress().port);

    RegisterAccountDialog registerAccountDialog(&networkManager);

    if (registerAccountDialog.exec() == QDialog::Accepted) {
        settingsManager.setAccount(SettingsManager::Account(registerAccountDialog.token()));
    }
}

void ActionBuilder::logout() {
    Settings::setValue<Account::Token>("");

    QStringList arguments = QCoreApplication::arguments();
    arguments.removeAt(0); // Remove application name
    QProcess::startDetached(QCoreApplication::applicationFilePath(), arguments);
    qApp->quit();
}

void ActionBuilder::about() {
    using namespace Const::App;

    QMessageBox::about(m_mainWindow, tr("About %1").arg(Name),
        tr("<h3>%1 %2</h3>"
          "IDE for Norm programming language<br><br>"
          "Based on Qt %3<br>"
          "Build on %4 %5<br><br>"
          "<a href=%6>%6</a><br><br>Copyright © %7, Vladimir Zarypov")
              .arg(Name, Version, QT_VERSION_STR, BuildDate, BuildTime, URL, CopyrightYear));
}
