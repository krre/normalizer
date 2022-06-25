#include "MainWindow.h"
#include "core/Constants.h"
#include "dialog/NewProject.h"
#include "project/Project.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);
    createWidgets();
    createActions();
    readSettings();
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::onNew() {
    NewProject newProject;

    if (newProject.exec() == QDialog::Rejected) return;

    Project project;
    project.create(newProject.path(), newProject.projectTemplate());
}

void MainWindow::onOpen() {

}

void MainWindow::onQuit() {
    writeSettings();
    QCoreApplication::quit();
}

void MainWindow::onAbout() {
    using namespace Const::App;

    QMessageBox::about(this, tr("About %1").arg(Name),
        tr("<h3>%1 %2 %3</h3>\
           IDE for Norm language<br><br> \
           Based on Qt %4<br> \
           Build on %5 %6<br><br> \
           <a href=%7>%7</a><br><br>Copyright © %8, Vladimir Zarypov")
           .arg(Name, Version, Status, QT_VERSION_STR, BuildDate, BuildTime, Url, CopyrightYear));
}

void MainWindow::onTabClosed(int index) {

}

void MainWindow::onTabClicked(int index) {

}

void MainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), this, &MainWindow::onNew, QKeySequence("Ctrl+N"));
    fileMenu->addAction(tr("Open..."), this, &MainWindow::onOpen, QKeySequence("Ctrl+O"));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), this, &MainWindow::onQuit, QKeySequence("Ctrl+Q"));

    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &MainWindow::onAbout);
}

void MainWindow::createWidgets() {
    tabWidget = new QTabWidget;
    tabWidget->setMinimumSize(QSize(0, 50));
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabClosed);
    connect(tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::onTabClicked);

    setCentralWidget(tabWidget);
}

void MainWindow::readSettings() {
    QSettings settings;

    QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();

    if (geometry.isEmpty()) {
        const QRect availableGeometry = QGuiApplication::screens().first()->availableGeometry();
        resize(availableGeometry.width() * 0.8, availableGeometry.height() * 0.8);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings() {
    QSettings settings;
    settings.setValue("geometry", saveGeometry());
}
