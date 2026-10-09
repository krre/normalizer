#include "MainWindow.h"
#include "core/Application.h"
#include "settings/FileSettings.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow() {
    setWindowTitle(Application::Name);

    m_fileSettings = new FileSettings(this);

    createActions();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::showNewProject() {
    qDebug() << "new project";
}

void MainWindow::showAbout() {
    QMessageBox::about(this, tr("About %1").arg(Application::Name),
tr(R"(<h3>%1 %2</h3>
IDE for Norm programming language<br><br>
Based on Qt %3<br>
Build on %4 %5<br><br>
<a href=%6>%6</a><br><br>
Copyright © %7, Vladimir Zarypov)")
        .arg(Application::Name, Application::Version, QT_VERSION_STR,
        Application::BuildDate, Application::BuildTime, Application::Url, Application::Years));
}

void MainWindow::readSettings() {
    if (!restoreGeometry(m_fileSettings->mainWindowGeometry())) {
        resize(screen()->size() * 0.75);
        move(screen()->availableGeometry().center() - rect().center());
    }

    restoreState(m_fileSettings->mainWindowState());
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindowGeometry(saveGeometry());
    m_fileSettings->setMainWindowState(saveState());
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));

    auto newMenu = fileMenu->addMenu(tr("New"));
    newMenu->addAction(tr("Project..."), Qt::CTRL | Qt::SHIFT | Qt::Key_N, this, &MainWindow::showNewProject);

    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}
