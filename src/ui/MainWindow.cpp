#include "MainWindow.h"
#include "ActionBuilder.h"
#include "RenderView.h"
#include "core/Constants.h"
#include "network/http/HttpNetwork.h"
#include "network/controller/project/NormProject.h"
#include "settings/FileSettings.h"
#include "widget/project/ProjectTable.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);

    m_fileSettings.reset(new FileSettings);
    m_httpNetwork.reset(new HttpNetwork(m_fileSettings->server().url));
    m_project.reset(new Controller::NormProject(m_httpNetwork.data()));

    m_projectTable.reset(new ProjectTable(m_project.data()));
    connect(m_projectTable.data(), &ProjectTable::opened, this, &MainWindow::openProject);

    ActionBuilder::Parameters parameters;
    parameters.mainWindow = this;
    parameters.projectTable = m_projectTable.data();
    parameters.httpNetwork = m_httpNetwork.data();
    parameters.fileSettings = m_fileSettings.data();

    m_actionBuilder = new ActionBuilder(parameters);
    connect(m_actionBuilder, &ActionBuilder::loggedChanged, m_projectTable.data(), &ProjectTable::setVisible);

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

void MainWindow::openProject(Id id) {
    m_renderView.reset(new RenderView(id));
    setToRootWidget(m_renderView.data());
    m_projectTable->setVisible(false);
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

    m_projectTable->setVisible(!m_fileSettings->account().token.isEmpty());
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindow(FileSettings::MainWindow(saveGeometry(), saveState()));
}
