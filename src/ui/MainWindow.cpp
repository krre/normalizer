#include "MainWindow.h"
#include "ActionBuilder.h"
#include "editor/CodeEditor.h"
#include "core/Application.h"
#include "external/network/http/HttpRestApi.h"
#include "external/settings/FileSettings.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(Application::Name);

    m_fileSettings.reset(new FileSettings);
    m_httpRestApi.reset(new HttpRestApi(m_fileSettings->developmentServer().url));

    ActionBuilder::Parameters parameters;
    parameters.mainWindow = this;
    parameters.httpNetwork = m_httpRestApi.data();
    parameters.fileSettings = m_fileSettings.data();

    m_actionBuilder = new ActionBuilder(parameters);
    m_rootWidget = new QWidget;
    setCentralWidget(m_rootWidget);

    readSettings();
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::openProject(Id id, const QString& name) {
    m_codeEditor.reset(new CodeEditor(id, m_httpRestApi.data(), m_fileSettings.data()));
    setToRootWidget(m_codeEditor.data());
    m_actionBuilder->updateFileActions(true);
    setWindowTitle(name + " - " + Application::Name);
}

void MainWindow::closeProject() {
    m_codeEditor.reset();
    m_actionBuilder->updateFileActions(false);
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
    QByteArray geometry = m_fileSettings->mainWindow().geometry;

    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    } else {
        const QRect availableGeometry = QGuiApplication::screens().constFirst()->availableGeometry();
        constexpr auto scale = 0.8;
        resize(availableGeometry.width() * scale, availableGeometry.height() * scale);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    }

    restoreState(m_fileSettings->mainWindow().state);
}

void MainWindow::writeSettings() {
    Settings::MainWindow mainWindow;
    mainWindow.geometry = saveGeometry();
    mainWindow.state = saveState();

    m_fileSettings->setMainWindow(mainWindow);
}
