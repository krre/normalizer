#include "ActionBuilder.h"
#include "MainWindow.h"
#include "project/Project.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "widget/Menu.h"
#include "widget/Action.h"
#include "widget/RecentMenu.h"
#include "dialog/Preferences.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(MainWindow* mainWindow, Project* project) : QObject(mainWindow),
        m_mainWindow(mainWindow), m_project(project) {
    QMenuBar* menuBar = mainWindow->menuBar();

    auto fileMenu = new Menu(tr("File"), menuBar);
    menuBar->addMenu(fileMenu);

    m_recentProjectsMenu = new RecentMenu(tr("Recent Projects"), menuBar);
    fileMenu->addAction(m_recentProjectsMenu->menuAction());
    connect(m_recentProjectsMenu, &RecentMenu::activated, m_project, &Project::open);

    fileMenu->addBindableAction(tr("Close"), Qt::CTRL | Qt::Key_W, project, &Project::close)->enabled().setBinding([this] { return m_project->opened().value(); });
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, mainWindow, &MainWindow::close);

    auto editMenu = new Menu(tr("Edit"), menuBar);
    menuBar->addMenu(editMenu);

    editMenu->addAction(tr("Preferences..."), this, &ActionBuilder::showPreferences);

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);
}

void ActionBuilder::showPreferences() {
    Preferences::Data data;
    data.host = QHostAddress(Settings::value<Server::Host>());
    data.port = Settings::value<Server::Port>();

    Preferences preferences(data);
    if (preferences.exec() == QDialog::Rejected) return;

    data = preferences.data();
    Settings::setValue<Server::Host>(data.host.toString());
    Settings::setValue<Server::Port>(data.port);
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
