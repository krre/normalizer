#include "MainWindow.h"
#include "ActionManager.h"
#include "SourceEditor.h"
#include "core/Constants.h"
#include "core/Settings.h"
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
    ProjectSettingsDialog projectSettingsDialog(projectPath);
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

void MainWindow::onTabClosed(int index) {
    QWidget* widget = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete widget;
}

void MainWindow::onTabClicked(int index) {
    if (index >= 0) {
        editor = static_cast<SourceEditor*>(tabWidget->widget(index));
        editor->setFocus();
    } else {
        editor = nullptr;
    }
}

int MainWindow::addSourceTab(const QString& filePath) {
    int tabIndex = findSource(filePath);

    if (tabIndex != -1) {
        tabWidget->setCurrentIndex(tabIndex);
        return tabIndex;
    } else {
        QFileInfo fi(filePath);
        editor = new SourceEditor(filePath);
        int index = tabWidget->addTab(editor, fi.baseName());
        tabWidget->setTabToolTip(index, filePath);
        tabWidget->setCurrentIndex(index);

        return index;
    }
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

void MainWindow::createTabWidget() {
    tabWidget = new QTabWidget;
    tabWidget->setMinimumSize(QSize(0, 50));
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::onTabClosed);
    connect(tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::onTabClicked);

    setCentralWidget(tabWidget);
}

void MainWindow::removeTabWidget() {
    setCentralWidget(nullptr);
    delete tabWidget;
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
    qInfo().noquote() << "Session readed:" << projectPath;
}

void MainWindow::writeSession() {
    if (!isProjectActive()) return;
    qInfo().noquote() << "Session writed:" << projectPath;
}

void MainWindow::addRecent(const QString& path) {
    if (!recentMenu->actions().count()) {
        recentMenu->addSeparator();
        recentMenu->addAction(tr("Clear Menu"), this, &MainWindow::onClearRecent);
    }

    for (QAction* action : recentMenu->actions()) {
        if (action->text() == path) {
            recentMenu->removeAction(action);
        }
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

    updateMenuState();
}

void MainWindow::updateMenuState() {
    recentMenu->setEnabled(recentMenu->actions().count());
    ActionManager::action(ActionManager::ProjectSettings)->setEnabled(isProjectActive());
    ActionManager::action(ActionManager::CloseProject)->setEnabled(isProjectActive());
}

void MainWindow::openProject(const QString& path) {
    closeProject();

    if (path.isEmpty()) return;

    createTabWidget();
    projectPath = path;
    qInfo().noquote() << "Project opened:" << path;

    if (Settings::Project::restoreSession()) {
        readSession();
    }

    addRecent(path);
    updateMenuState();

    QFileInfo fi(projectPath);
    setWindowTitle(QString(Const::App::Name) + " - " + fi.baseName());
}

void MainWindow::closeProject() {
    if (!isProjectActive()) return;

    if (Settings::Project::restoreSession()) {
        writeSession();
    }

    removeTabWidget();
    qInfo().noquote() << "Project closed:" << projectPath;
    projectPath = QString();
    updateMenuState();
    setWindowTitle(Const::App::Name);
}

bool MainWindow::isProjectActive() const {
    return !projectPath.isEmpty();
}

int MainWindow::findSource(const QString& filePath) {
    for (int i = 0; i < tabWidget->count(); i++) {
        auto editor = static_cast<SourceEditor*>(tabWidget->widget(i));

        if (editor->filePath() == filePath) {
            return i;
        }
    }

    return -1;
}

void MainWindow::closeWindow() {
    Settings::Project::setLast(Settings::Project::openLast() ? projectPath : QString());
    closeProject();
    writeSettings();
}
