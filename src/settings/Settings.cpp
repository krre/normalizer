#include "Settings.h"
#include "core/Application.h"
#include <QStandardPaths>

namespace MainWindow {
    constexpr auto Geometry = "MainWindow/geometry";
    constexpr auto State = "MainWindow/state";
}

namespace Ui {
    constexpr auto LoadLastProject = "Ui/loadLastProject";
    constexpr auto LastProjectPath = "Ui/lastProjectPath";
}

namespace Network {
    constexpr auto Host = "Network/host";
    constexpr auto Port = "Network/port";
}

namespace Path {
    constexpr auto Workspace = "Path/workspace";
}

namespace Logging {
    constexpr auto Vulkan = "Logging/vulkan";
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

void Settings::setUiLoadLastProject(bool load) {
    setValue(Ui::LoadLastProject, load);
}

bool Settings::uiLoadLastProject() const {
    return value(Ui::LoadLastProject, true).toBool();
}

void Settings::setUiLastProjectPath(const QString& path) {
    setValue(Ui::LastProjectPath, path);
}

QString Settings::uiLastLoadPath() const {
    return value(Ui::LastProjectPath).toString();
}

void Settings::setNetworkHost(const QString& host) {
    setValue(Network::Host, host);
}

QString Settings::networkHost() const {
    return value(Network::Host, "ws://127.0.0.1").toString();
}

void Settings::setNetworkPort(int port) {
    setValue(Network::Port, port);
}

int Settings::networkPort() const {
    return value(Network::Port, 3010).toInt();
}

void Settings::setPathWorkspace(const QString& workspace) {
    setValue(Path::Workspace, workspace);
}

QString Settings::pathWorkspace() const {
    return value(Path::Workspace, QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + Application::WorkspaceName).toString();
}

void Settings::setLoggingVulkan(bool enable) {
    setValue(Logging::Vulkan, enable);
}

bool Settings::loggingVulkan() const {
    return value(Logging::Vulkan, false).toBool();
}
