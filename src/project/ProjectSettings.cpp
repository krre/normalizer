#include "ProjectSettings.h"
#include "core/Constants.h"
#include <QtCore>

ProjectSettings::ProjectSettings()  {
}

void ProjectSettings::create() {
    QDir dir;
    dir.mkpath(dirPath());

    setFormat(NormCommon::Project::Format::Binary);
}

void ProjectSettings::load() {
    QFile file(filePath());

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning().noquote() << "Failed to open project settings file for reading:" << filePath();
        return;
    }

    settings = QJsonDocument::fromJson(file.readAll()).object();
}

void ProjectSettings::save() {
    QFile file(filePath());

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning().noquote() << "Failed to open project settings file for writing:" << filePath();
        return;
    }

    file.write(QJsonDocument(settings).toJson());
}

void ProjectSettings::clear() {
    m_projectPath = QString();
    settings = QJsonObject();
}

bool ProjectSettings::isValid() const {
    return !m_projectPath.isEmpty();
}

QString ProjectSettings::projectPath() const {
    return m_projectPath;
}

void ProjectSettings::setProjectPath(const QString& path) {
    m_projectPath = path;
}

NormCommon::Project::Format ProjectSettings::format() const {
    return static_cast<NormCommon::Project::Format>(settings["format"].toInt());
}

void ProjectSettings::setFormat(NormCommon::Project::Format format) {
    settings["format"] = static_cast<int>(format);
}

QString ProjectSettings::dirPath() const {
    return m_projectPath + "/" + Const::Project::DataDir;
}

QString ProjectSettings::filePath() const {
    return dirPath() + "/" + Const::Project::SettingsFile;
}
