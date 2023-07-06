#include "ActionBuilder.h"
#include "MainWindow.h"
#include "RecentProjectsMenu.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "widget/Menu.h"
#include "widget/Action.h"
#include "dialog/NewProject.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(MainWindow* mainWindow, Project* project) : QObject(mainWindow),
        m_mainWindow(mainWindow), m_project(project) {
    QMenuBar* menuBar = mainWindow->menuBar();

    auto fileMenu = new Menu(tr("File"), menuBar);
    menuBar->addMenu(fileMenu);

    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &ActionBuilder::newProject);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &ActionBuilder::open);

    m_recentProjectsMenu = new RecentProjectsMenu(tr("Recent Projects"), menuBar);
    fileMenu->addAction(m_recentProjectsMenu->menuAction());
    connect(m_recentProjectsMenu, &RecentProjectsMenu::activated, m_project, &Project::open);

    fileMenu->addBindableAction(tr("Save"), Qt::CTRL | Qt::Key_S, project, &Project::save)->enabled().setBinding([this] { return m_project->opened().value(); });
    fileMenu->addBindableAction(tr("Close"), Qt::CTRL | Qt::Key_W, project, &Project::close)->enabled().setBinding([this] { return m_project->opened().value(); });
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, mainWindow, &MainWindow::close);

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);
}

void ActionBuilder::newProject() {
    NewProject newProject(Settings::value<General::Workspace>());
    if (newProject.exec() == QDialog::Rejected) return;

    try {
        m_project->create(newProject.name(), newProject.directory(), newProject.projectTemplate());
        Settings::setValue<General::Workspace>(newProject.directory());
    } catch (ProjectExists&) {
        QMessageBox::critical(m_mainWindow, tr("Creating project"), tr("Project already exists"));
    }
}

void ActionBuilder::open() {
    QString dirPath = QFileDialog::getExistingDirectory(m_mainWindow, tr("Open Norm Project"), Settings::value<General::Workspace>());

    if (!dirPath.isEmpty()) {
        m_project->open(dirPath);
    }
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
