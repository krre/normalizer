#include "Settings.h"
#include "core/Application.h"
#include <QStandardPaths>

namespace MainWindow {
    constexpr auto Geometry = "MainWindow/geometry";
    constexpr auto State = "MainWindow/state";
}

namespace Path {
    constexpr auto Workspace = "Path/workspace";
}

void Settings::setMainWindowGeometry(const QByteArray& geometry) {
    setValue(MainWindow::Geometry, geometry);
}

QByteArray Settings::mainWindowGeometry() const {
    return value(MainWindow::Geometry).toByteArray();
}

void Settings::setMainWindowState(const QByteArray& state) {
    setValue(MainWindow::State, state);
}

QByteArray Settings::mainWindowState() const {
    return value(MainWindow::State).toByteArray();
}

void Settings::setPathWorkspace(const QString& workspace) {
    setValue(Path::Workspace, workspace);
}

QString Settings::pathWorkspace() const {
    return value(Path::Workspace, QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + Application::WorkspaceName).toString();
}
