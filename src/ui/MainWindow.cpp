#include "MainWindow.h"
#include "core/Application.h"
#include "settings/FileSettings.h"
#include <QCloseEvent>

MainWindow::MainWindow() {
    m_fileSettings = new FileSettings(this);

    setWindowTitle(Application::Name);
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    writeSettings();
    event->accept();
}

void MainWindow::readSettings() {
    if (!restoreGeometry(m_fileSettings->mainWindowGeometry())) {
        const auto screenSize = screen()->size();
        constexpr auto scale = 0.75;
        resize(screenSize.width() * scale, screenSize.height() * scale);
        move((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2);
    }

    restoreState(m_fileSettings->mainWindowState());
}

void MainWindow::writeSettings() {
    m_fileSettings->setMainWindowGeometry(saveGeometry());
    m_fileSettings->setMainWindowState(saveState());
}
