#include "MainWindow.h"
#include "core/Application.h"
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow() {
    setWindowTitle(Application::applicationName());
    createActions();
    resize(800, 600);
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

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}
