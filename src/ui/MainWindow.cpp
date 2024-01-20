#include "MainWindow.h"
#include "ActionBuilder.h"
#include "editor/CodeEditor.h"
#include "core/Application.h"
#include "external/network/http/HttpRestApi.h"
#include "external/settings/FileSettings.h"
#include "widget/project/ProjectTable.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Application::Name);

    m_fileSettings.reset(new FileSettings);
    m_httpRestApi.reset(new HttpRestApi(m_fileSettings->server().api));

    m_projectTable.reset(new ProjectTable(m_httpRestApi.data()));
    m_projectTable->setVisible(false);
    connect(m_projectTable.data(), &ProjectTable::opened, this, &MainWindow::openProject);

    ActionBuilder::Parameters parameters;
    parameters.mainWindow = this;
    parameters.projectTable = m_projectTable.data();
    parameters.httpNetwork = m_httpRestApi.data();
    parameters.fileSettings = m_fileSettings.data();

    m_actionBuilder = new ActionBuilder(parameters);
    connect(m_actionBuilder, &ActionBuilder::loggedChanged, m_projectTable.data(), &ProjectTable::setVisible);
    connect(m_actionBuilder, &ActionBuilder::projectClosed, this, &MainWindow::closeProject);

    m_rootWidget = new QWidget;
    setCentralWidget(m_rootWidget);

    setToRootWidget(m_projectTable.data());

    readSettings();
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::openProject(Id id, const QString& name) {
    m_codeEditor.reset(new CodeEditor(id, m_fileSettings.data()));
    setToRootWidget(m_codeEditor.data());
    m_projectTable->setVisible(false);

    m_actionBuilder->updateProjectActions();
    m_actionBuilder->updateAccountActions();

    FileSettings::Project project = m_fileSettings->project();
    project.id = id;
    project.name = name;
    m_fileSettings->setProject(project);

    setWindowTitle(name + " - " + Application::Name);
}

void MainWindow::closeProject() {
    m_codeEditor.reset();
    setToRootWidget(m_projectTable.data());
    m_projectTable->setVisible(true);

    m_actionBuilder->updateProjectActions();
    m_actionBuilder->updateAccountActions();

    FileSettings::Project project = m_fileSettings->project();
    project.id = 0;
    project.name = "";
    m_fileSettings->setProject(project);

    setWindowTitle(Application::Name);
}

void MainWindow::setToRootWidget(QWidget* widget) {
    if (m_rootWidget->layout()) {
        delete m_rootWidget->layout();
    }

    auto layout = new QVBoxLayout(m_rootWidget);
    layout->setContentsMargins(QMargins());
    layout->addWidget(widget);

    m_rootWidget->setLayout(layout);
}

void MainWindow::readSettings() {
    if (m_fileSettings->containsGeometry()) {
        restoreGeometry(m_fileSettings->mainWindow().geometry);
        restoreState(m_fileSettings->mainWindow().state);
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        constexpr auto scale = 0.8;
        resize(availableGeometry.width() * scale, availableGeometry.height() * scale);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    if (!m_fileSettings->account().token.isEmpty()) {
        FileSettings::Project project = m_fileSettings->project();

        if (project.id) {
            openProject(project.id, project.name);
        } else {
            m_projectTable->setVisible(true);

            QTimer::singleShot(0, this, [this] {
                m_actionBuilder->updateAccountActions();
            });

        }
    }
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindow(FileSettings::MainWindow(saveGeometry(), saveState()));
}
