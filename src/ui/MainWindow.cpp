#include "MainWindow.h"
#include "ActionManager.h"
#include "SourceEditor.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "core/Global.h"
#include "project/ProjectSettings.h"
#include "dialog/NewProject.h"
#include "dialog/Options.h"
#include "dialog/ProjectSettingsDialog.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);
    createWidgets();
    createActions();
    readSettings();
    updateMenuState();
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent* event) {
    closeWindow();
    event->accept();
}

void MainWindow::onNew() {
    NewProject newProject;

    if (newProject.exec() == QDialog::Accepted) {
        qInfo().noquote() << "Project created:" << newProject.path();
        openProject(newProject.path());
    }
}

void MainWindow::onOpen() {
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Norm Project"), Settings::Project::workspace());
    if (dirPath.isEmpty()) return;

    openProject(dirPath);
}

void MainWindow::onClose() {
    closeProject();
}

void MainWindow::onClearRecent() {
    recentMenu->clear();
    updateMenuState();
}

void MainWindow::onProjectSettings() {
    ProjectSettingsDialog projectSettingsDialog;
    projectSettingsDialog.exec();
}

void MainWindow::onQuit() {
    closeWindow();
    QCoreApplication::quit();
}

void MainWindow::onOptions() {
    Options options;
    options.exec();
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

void MainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("File"));
    ActionManager::addAction(ActionManager::NewProject, fileMenu->addAction(tr("New..."), this, &MainWindow::onNew, QKeySequence("Ctrl+N")));
    ActionManager::addAction(ActionManager::OpenProject,fileMenu->addAction(tr("Open..."), this, &MainWindow::onOpen, QKeySequence("Ctrl+O")));
    ActionManager::addAction(ActionManager::CloseProject, fileMenu->addAction(tr("Close"), this, &MainWindow::onClose, QKeySequence("Ctrl+W")));
    recentMenu = fileMenu->addMenu(tr("Recent Projects"));
    fileMenu->addSeparator();
    ActionManager::addAction(ActionManager::ProjectSettings, fileMenu->addAction(tr("Project Settings..."), this, &MainWindow::onProjectSettings));
    fileMenu->addSeparator();
    ActionManager::addAction(ActionManager::Exit, fileMenu->addAction(tr("Exit"), this, &MainWindow::onQuit, QKeySequence("Ctrl+Q")));

    QMenu* toolsMenu = menuBar()->addMenu(tr("Tools"));
    toolsMenu->addAction(tr("Options..."), this, &MainWindow::onOptions);

    QMenu* helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &MainWindow::onAbout);
}

void MainWindow::createWidgets() {

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
        const QRect availableGeometry = QGuiApplication::screens().first()->availableGeometry();
        resize(availableGeometry.width() * 0.8, availableGeometry.height() * 0.8);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }

    QStringList recentProjects = Settings::Project::recent();

    for (int i = recentProjects.count() - 1; i >= 0; i--) {
        addRecent(recentProjects.at(i));
    }

    if (Settings::Project::openLast()) {
        openProject(Settings::Project::last());
    }
}

void MainWindow::writeSettings() {
    Settings::MainWindow::setGeometry(saveGeometry());

    QStringList recentProjects;

    for (int i = 0; i < recentMenu->actions().count(); i++) {
        if (recentMenu->actions().at(i)->isSeparator()) {
            break;
        }

        recentProjects.append(recentMenu->actions().at(i)->text());
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

void MainWindow::addRecent(const QString& path) {
    auto c = qScopeGuard([=] { updateMenuState(); });

    if (!recentMenu->actions().count()) {
        recentMenu->addSeparator();
        recentMenu->addAction(tr("Clear Menu"), this, &MainWindow::onClearRecent);
    }

    for (QAction* action : recentMenu->actions()) {
        if (action->text() == path) {
            recentMenu->removeAction(action);
        }
    }

    if (!QFileInfo::exists(path)) {
        return;
    }

    QAction* action = new QAction(path);
    connect(action, &QAction::triggered, this, [=] {
        openProject(path);
    });

    recentMenu->insertAction(recentMenu->actions().constFirst(), action);
    const int SEPARATOR_AND_CLEAR = 2;

    if (recentMenu->actions().size() > Const::Window::MaxRecentFiles + SEPARATOR_AND_CLEAR) {
        recentMenu->removeAction(recentMenu->actions().at(recentMenu->actions().size() - SEPARATOR_AND_CLEAR - 1));
    }
}

void MainWindow::updateMenuState() {
    if (recentMenu->actions().count() && recentMenu->actions().first()->isSeparator()) {
        recentMenu->clear();
    }

    recentMenu->setEnabled(recentMenu->actions().count());
    ActionManager::action(ActionManager::ProjectSettings)->setEnabled(isProjectActive());
    ActionManager::action(ActionManager::CloseProject)->setEnabled(isProjectActive());
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

    addRecent(path);

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

    updateMenuState();
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
