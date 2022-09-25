#include "MainWindow.h"
#include "TopMenu.h"
#include "SourceEditor.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "core/Global.h"
#include "project/ProjectSettings.h"
#include "project/Project.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);
    topMenu = new TopMenu(this);
    readSettings();
    topMenu->updateState();
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent* event) {
    closeWindow();
    event->accept();
}

void MainWindow::createSourceEditor() {
    sourceEditor = new SourceEditor(this);
    setCentralWidget(sourceEditor);
}

void MainWindow::removeSourceEditor() {
    setCentralWidget(nullptr);
    delete sourceEditor;
    sourceEditor = nullptr;
}

void MainWindow::readSettings() {
    QByteArray geometry = Settings::MainWindow::geometry();

    if (geometry.isEmpty()) {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        resize(availableGeometry.width() * 0.8, availableGeometry.height() * 0.8);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }

    QStringList recentProjects = Settings::Project::recent();

    for (int i = recentProjects.count() - 1; i >= 0; i--) {
        topMenu->addRecent(recentProjects.at(i));
    }

    if (Settings::Project::openLast()) {
        openProject(Settings::Project::last());
    }
}

void MainWindow::writeSettings() {
    Settings::MainWindow::setGeometry(saveGeometry());

    QStringList recentProjects;

    for (int i = 0; i < topMenu->recent()->actions().count(); i++) {
        if (topMenu->recent()->actions().at(i)->isSeparator()) {
            break;
        }

        recentProjects.append(topMenu->recent()->actions().at(i)->text());
    }

    Settings::Project::setRecent(recentProjects);
}

void MainWindow::readSession() {
    if (!isProjectActive()) return;
    qInfo().noquote() << "Session readed:" << Global::projectSettings()->projectPath();
}

void MainWindow::writeSession() {
    if (!isProjectActive()) return;
    qInfo().noquote() << "Session writed:" << Global::projectSettings()->projectPath();
}

void MainWindow::openProject(const QString& path) {
    closeProject();

    if (path.isEmpty()) return;
    if (!QFileInfo::exists(path)) return;

    createSourceEditor();

    auto projectSettings = Global::projectSettings();
    projectSettings->setProjectPath(path);
    projectSettings->load();

    Global::project()->open(path);

    qInfo().noquote() << "Project opened:" << path;

    if (Settings::Project::restoreSession()) {
        readSession();
    }

    topMenu->addRecent(path);

    QFileInfo fi(path);
    setWindowTitle(QString(Const::App::Name) + " - " + fi.baseName());
}

void MainWindow::closeProject() {
    if (!isProjectActive()) return;

    if (Settings::Project::restoreSession()) {
        writeSession();
    }

    removeSourceEditor();

    auto projectSettings = Global::projectSettings();
    QString projectPath = projectSettings->projectPath();
    projectSettings->clear();

    Global::project()->close();

    qInfo().noquote() << "Project closed:" << projectPath;

    topMenu->updateState();
    setWindowTitle(Const::App::Name);
}

bool MainWindow::isProjectActive() const {
    return Global::projectSettings()->isValid();
}

void MainWindow::closeWindow() {
    Settings::Project::setLast(Settings::Project::openLast() ? Global::projectSettings()->projectPath() : QString());
    closeProject();
    writeSettings();
}
