#include "TopMenu.h"
#include "MainWindow.h"
#include "ActionManager.h"
#include "core/Constants.h"
#include "core/Global.h"
#include "core/Settings.h"
#include "dialog/NewProject.h"
#include "dialog/Preferences.h"
#include "dialog/ProjectSettings.h"
#include "project/ProjectSettings.h"
#include <QtWidgets>

TopMenu::TopMenu(MainWindow* mainWindow) : QObject(mainWindow), mainWindow(mainWindow) {
    QMenu* fileMenu = mainWindow->menuBar()->addMenu(tr("File"));
    ActionManager::addAction(ActionManager::NewProject, fileMenu->addAction(tr("New..."), this, &TopMenu::onNew, QKeySequence("Ctrl+N")));
    ActionManager::addAction(ActionManager::OpenProject, fileMenu->addAction(tr("Open..."), this, &TopMenu::onOpen, QKeySequence("Ctrl+O")));
    ActionManager::addAction(ActionManager::CloseProject, fileMenu->addAction(tr("Close"), this, &TopMenu::onClose, QKeySequence("Ctrl+W")));
    recentMenu = fileMenu->addMenu(tr("Recent Projects"));
    fileMenu->addSeparator();
    ActionManager::addAction(ActionManager::ProjectSettings, fileMenu->addAction(tr("Project Settings..."), this, &TopMenu::onProjectSettings));
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Preferences..."), this, &TopMenu::onPreferences);
    fileMenu->addSeparator();
    ActionManager::addAction(ActionManager::Exit, fileMenu->addAction(tr("Exit"), mainWindow, &QMainWindow::close, QKeySequence("Ctrl+Q")));

    editMenu = mainWindow->menuBar()->addMenu(tr("Edit"));
    ActionManager::addAction(ActionManager::Undo, editMenu->addAction(tr("Undo"), this, &TopMenu::onUndo, QKeySequence("Ctrl+Z")));
    ActionManager::addAction(ActionManager::Redo, editMenu->addAction(tr("Redo"), this, &TopMenu::onRedo, QKeySequence("Ctrl+Shift+Z")));

    unitMenu = mainWindow->menuBar()->addMenu(tr("Unit"));

    addMenu = unitMenu->addMenu(tr("Add"));
    ActionManager::addAction(ActionManager::AddOperator, addMenu->addAction(tr("Operator"), this, &TopMenu::onAddOperator));
    ActionManager::addAction(ActionManager::AddExpression, addMenu->addAction(tr("Expression"), this, &TopMenu::onAddExpression));

    buildMenu = mainWindow->menuBar()->addMenu(tr("Build"));
    ActionManager::addAction(ActionManager::Build, buildMenu->addAction(tr("Build"), this, &TopMenu::onBuild, QKeySequence("Ctrl+B")));
    ActionManager::addAction(ActionManager::Run, buildMenu->addAction(tr("Run"), this, &TopMenu::onRun, QKeySequence("Ctrl+R")));

    QMenu* helpMenu = mainWindow->menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &TopMenu::onAbout);
}

void TopMenu::updateState() {
    if (recentMenu->actions().count() && recentMenu->actions().constFirst()->isSeparator()) {
        recentMenu->clear();
    }

    recentMenu->setEnabled(recentMenu->actions().count());
    editMenu->setEnabled(isProjectActive());
    unitMenu->setEnabled(isProjectActive());
    addMenu->setEnabled(isProjectActive());
    buildMenu->setEnabled(isProjectActive());
    ActionManager::action(ActionManager::ProjectSettings)->setEnabled(isProjectActive());
    ActionManager::action(ActionManager::CloseProject)->setEnabled(isProjectActive());
}

void TopMenu::addRecent(const QString& path) {
    auto c = qScopeGuard([=] { updateState(); });

    if (!recentMenu->actions().count()) {
        recentMenu->addSeparator();
        recentMenu->addAction(tr("Clear Menu"), this, &TopMenu::onClearRecent);
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
        mainWindow->openProject(path);
    });

    recentMenu->insertAction(recentMenu->actions().constFirst(), action);
    const int SEPARATOR_AND_CLEAR = 2;

    if (recentMenu->actions().size() > Const::Window::MaxRecentFiles + SEPARATOR_AND_CLEAR) {
        recentMenu->removeAction(recentMenu->actions().at(recentMenu->actions().size() - SEPARATOR_AND_CLEAR - 1));
    }
}

QMenu* TopMenu::recent() const {
    return recentMenu;
}

void TopMenu::onNew() {
    Dialog::NewProject newProject;

    if (newProject.exec() == QDialog::Accepted) {
        qInfo().noquote() << "Project created:" << newProject.path();
        mainWindow->openProject(newProject.path());
    }
}

void TopMenu::onOpen() {
    QString dirPath = QFileDialog::getExistingDirectory(mainWindow, tr("Open Norm Project"), Settings::Project::workspace());
    if (dirPath.isEmpty()) return;

    mainWindow->openProject(dirPath);
}

void TopMenu::onClose() {
    mainWindow->closeProject();
}

void TopMenu::onClearRecent() {
    recentMenu->clear();
    updateState();
}

void TopMenu::onProjectSettings() {
    Dialog::ProjectSettings projectSettings;
    projectSettings.exec();
}

void TopMenu::onUndo() {

}

void TopMenu::onRedo() {

}

void TopMenu::onAddOperator() {

}

void TopMenu::onAddExpression() {

}

void TopMenu::onBuild() {

}

void TopMenu::onRun() {

}

void TopMenu::onPreferences() {
    Dialog::Preferences preferences;
    preferences.exec();
}

void TopMenu::onAbout() {
    using namespace Const::App;

    QMessageBox::about(mainWindow, tr("About %1").arg(Name),
        tr("<h3>%1 %2 %3</h3>\
           IDE for Norm language<br> \
           Supported Norm %4<br><br> \
           Based on Qt %5<br> \
           Build on %6 %7<br><br> \
           <a href=%8>%8</a><br><br>Copyright © %9, Vladimir Zarypov")
           .arg(Name, Global::Version::application().toString(), Status, Global::Version::language().toString(),
                QT_VERSION_STR, BuildDate, BuildTime, Url, CopyrightYear));
}

bool TopMenu::isProjectActive() const {
    return Global::projectSettings()->isValid();
}
