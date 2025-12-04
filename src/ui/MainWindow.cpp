#include "MainWindow.h"
#include "core/Application.h"
#include "project/Project.h"
#include "ui/dialog/NewProject.h"
#include "ui/dialog/Preferences.h"
#include "settings/Settings.h"
#include "editor/CodeEditor.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>

MainWindow::MainWindow(Settings* settings) : m_settings(settings) {
    m_project = new Project(this);

    changeWindowTitle();
    createActions();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    writeSettings();
    event->accept();
}

void MainWindow::createProject() {
    NewProject newProject(m_settings->pathWorkspace());

    if (newProject.exec() == QDialog::Accepted) {
        m_project->create(newProject.name(), newProject.directory(), newProject.target());
        createCodeEditor();
        changeWindowTitle();
    }
}

void MainWindow::openProject() {
    QString path = QFileDialog::getExistingDirectory(this);

    if (path.isEmpty()) {
        return;
    }

    m_project->open(path);
    createCodeEditor();
    changeWindowTitle();
}

void MainWindow::closeProject() {
    m_project->reset();
    m_codeEditor = nullptr;
    setCentralWidget(nullptr);
    changeWindowTitle();
}

void MainWindow::showPreferences() {
    Preferences preferences(m_settings);
    preferences.exec();
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
    QByteArray geometry = m_settings->mainWindowGeometry();

    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    } else {
        const auto screenSize = screen()->size();
        constexpr auto scale = 0.75;
        resize(screenSize.width() * scale, screenSize.height() * scale);
        move((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2);
    }

    restoreState(m_settings->mainWindowState());
}

void MainWindow::writeSettings() {
    m_settings->setMainWindowGeometry(saveGeometry());
    m_settings->setMainWindowState(saveState());
}

void MainWindow::changeWindowTitle() {
    QString title = Application::applicationName();

    if (m_project->isValid()) {
        title = m_project->name() + " - " + title;
    }

    setWindowTitle(title);
}

void MainWindow::createActions() {
    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New..."), Qt::CTRL | Qt::Key_N, this, &MainWindow::createProject);
    fileMenu->addAction(tr("Open..."), Qt::CTRL | Qt::Key_O, this, &MainWindow::openProject);
    fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, this, &MainWindow::closeProject);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Preferences..."), this, &MainWindow::showPreferences);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);
}

void MainWindow::createCodeEditor() {
    m_codeEditor = new CodeEditor;
    setCentralWidget(m_codeEditor);
}
