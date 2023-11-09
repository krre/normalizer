#include "MainWindow.h"
#include "ActionBuilder.h"
#include "RenderView.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "manager/network/HttpNetworkManager.h"
#include "manager/settings/FileSettingsStorage.h"
#include "widget/project/ProjectTable.h"
#include "project/Project.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Const::App::Name);

    m_fileSettingsStorage.reset(new FileSettingsStorage);
    m_httpNetworkManager.reset(new HttpNetworkManager(m_fileSettingsStorage->serverAddress().host, m_fileSettingsStorage->serverAddress().port));

    m_projectTable = new ProjectTable;
    m_renderView = new RenderView;
    m_project = new Project(m_renderView, this);

    ActionBuilder::Parameters parameters;
    parameters.mainWindow = this;
    parameters.project = m_project;
    parameters.httpNetworkManager = m_httpNetworkManager.data();
    parameters.fileSettingsStorage = m_fileSettingsStorage.data();

    m_actionBuilder = new ActionBuilder(parameters);

    m_projectPathNotifier = m_project->path().addNotifier([&] {
        QFileInfo fi(m_project->path().value());
        setWindowTitle((!fi.baseName().isEmpty() ? fi.baseName() + " - " : "") + Const::App::Name);
    });

    setCentralWidget(m_projectTable);

    readSettings();

    QString projectPath = Settings::value<General::LastProject>();
    m_project->open(projectPath);
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::readSettings() {
    if (Settings::contains<General::Geometry>()) {
        restoreGeometry(Settings::value<General::Geometry>());
        restoreState(Settings::value<General::State>());
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        constexpr auto scale = 0.8;
        resize(availableGeometry.width() * scale, availableGeometry.height() * scale);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }
}

void MainWindow::writeSettings() {
    Settings::setValue<General::Geometry>(saveGeometry());
    Settings::setValue<General::State>(saveState());
}
