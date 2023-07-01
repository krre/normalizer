#include "MainWindow.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "ActionBuilder.h"
#include "RenderView.h"
#include "project/Project.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);
    readSettings();

    m_project = new Project(this);
    m_actionBuilder = new ActionBuilder(this, m_project);
    m_renderView = new RenderView;
    setCentralWidget(m_renderView);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::readSettings() {
    if (Settings::contains(Settings::Geometry())) {
        restoreGeometry(Settings::value(Settings::Geometry()));
        restoreState(Settings::value(Settings::State()));
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        constexpr auto scale = 0.8;
        resize(availableGeometry.width() * scale, availableGeometry.height() * scale);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}

void MainWindow::writeSettings() {
    Settings::setValue(Settings::Geometry(), saveGeometry());
    Settings::setValue(Settings::State(), saveState());
}
