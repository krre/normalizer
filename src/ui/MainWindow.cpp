#include "MainWindow.h"
#include "core/Application.h"
#include "project/Project.h"
#include "ui/dialog/NewProject.h"
#include "ui/dialog/NewWorkspace.h"
#include "ui/dialog/Preferences.h"
#include "settings/Settings.h"
#include "network/Network.h"
#include "network/api/common/Server.h"
#include "editor/CodeEditor.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QSettings>

MainWindow::MainWindow(Settings* settings) : m_settings(settings) {
    m_project = new Project(this);

    m_webSocketClient = new WebSocketClient(QUrl(settings->serverHost() + ":" + QString::number(settings->serverPort())), this);
    connect(m_webSocketClient, &WebSocketClient::stateChanged, this, &MainWindow::setConnectionState);

    m_network = new Network(m_webSocketClient, this);

    m_statusLabel = new QLabel;
    m_statusLabel->setContentsMargins(4, 0, 0, 0);
    statusBar()->addWidget(m_statusLabel);

    changeWindowTitle();
    createActions();
    readSettings();

    setConnectionState(m_webSocketClient->state());
    m_webSocketClient->connect();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::createWorkspace() {
    NewWorkspace newWorkspace;

    if (newWorkspace.exec() == QDialog::Accepted) {

    }
}

void MainWindow::createProject() {
    NewProject newProject;

    if (newProject.exec() == QDialog::Accepted) {
        m_project->create(newProject.name(), newProject.directory(), newProject.target());
        openProjectFromPath(newProject.directory() + "/" + newProject.name());
    }
}

void MainWindow::closeProject() {
    m_project->reset();
    m_codeEditor = nullptr;
    setCentralWidget(nullptr);
    changeWindowTitle();
    m_settings->setUiLastProjectPath(QString());
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

void MainWindow::setConnectionState(WebSocketClient::State state) {
    QString connectionMessage;

    switch (state) {
        case WebSocketClient::State::Connecting:
            connectionMessage = tr("Connecting...");
            break;
        case WebSocketClient::State::Connected:
            connectionMessage = tr("Connected");
            onConnected();
            break;
        case WebSocketClient::State::Disconnected:
            connectionMessage = tr("Disconnected");
            onDisconnected();
            break;
        default:
            break;
    }

    m_statusLabel->setText(connectionMessage);
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

    if (m_settings->uiLoadLastProject()) {
        openProjectFromPath(m_settings->uiLastLoadPath());
    }
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

    auto newMenu = fileMenu->addMenu(tr("New"));
    newMenu->addAction(tr("Workspace..."), this, &MainWindow::createWorkspace);
    newMenu->addAction(tr("Project..."), this, &MainWindow::createProject);

    auto closeAction = fileMenu->addAction(tr("Close"), Qt::CTRL | Qt::Key_W, this, &MainWindow::closeProject);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, this, &QMainWindow::close);

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    editMenu->addAction(tr("Preferences..."), this, &MainWindow::showPreferences);

    auto helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Application::Name), this, &MainWindow::showAbout);

    closeAction->setEnabled(false);

    connect(m_project, &Project::stateChanged, [=] (Project::State state) {
        closeAction->setEnabled(state != Project::State::Uninitialized);
    });
}

void MainWindow::createCodeEditor() {
    m_codeEditor = new CodeEditor;
    setCentralWidget(m_codeEditor);
}

void MainWindow::openProjectFromPath(const QString& path) {
     if (!QFile::exists(path)) return;

    m_project->open(path);
    createCodeEditor();
    changeWindowTitle();
    m_settings->setUiLastProjectPath(path);
}

Async::Task<void> MainWindow::onConnected() {
    Api::Server server(m_network);
    Api::Server::Attributes attributes = co_await server.handshake();
    qDebug() << attributes.version;
}

void MainWindow::onDisconnected() {

}
