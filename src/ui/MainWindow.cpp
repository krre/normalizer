#include "MainWindow.h"
#include "ActionBuilder.h"
#include "RenderView.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "widget/RecentMenu.h"
#include "project/Project.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);

    m_renderView = new RenderView;
    m_project = new Project(m_renderView, this);
    m_actionBuilder = new ActionBuilder(this, m_project);

    m_projectPathNotifier = m_project->path().addNotifier([&] {
        QFileInfo fi(m_project->path().value());
        setWindowTitle((!fi.baseName().isEmpty() ? fi.baseName() + " - " : "") + Const::App::Name);
        m_actionBuilder->recentProjectsMenu()->addPath(m_project->path().value());
    });

    setCentralWidget(m_renderView);

    readSettings();

    QString projectPath = Settings::value<General::LastProject>();
    m_project->open(projectPath);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::readSettings() {
    if (Settings::contains<General::Geometry>()) {
        restoreGeometry(Settings::value<General::Geometry>());
        restoreState(Settings::value<General::State>());
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        constexpr auto scale = 0.8;
        resize(availableGeometry.width() * scale, availableGeometry.height() * scale);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    m_actionBuilder->recentProjectsMenu()->setPathes(Settings::value<General::RecentProjects>());
}

void MainWindow::writeSettings() {
    Settings::setValue<General::Geometry>(saveGeometry());
    Settings::setValue<General::State>(saveState());
    Settings::setValue<General::RecentProjects>(m_actionBuilder->recentProjectsMenu()->pathes());
}
