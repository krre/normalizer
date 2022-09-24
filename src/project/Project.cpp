#include "Project.h"
#include "core/Utils.h"
#include <QtCore>

Project::Project() {

}

QString Project::path() const {
    return m_path;
}

Project::Target Project::target() const {
    return m_target;
}

void Project::create(const QString& path, Target target) {
    QString filePath;

    switch (target) {
        case Target::Application: filePath = Utils::applicationPath(path); break;
        case Target::Library: filePath = Utils::libraryPath(path); break;
        default: throw std::runtime_error("Unknown project target"); break;
    }

    QFile file(filePath);

    if (!file.open(QIODeviceBase::WriteOnly)) {
        qWarning().noquote() << "Failed to open project file for writing:" << filePath;
        return;
    }

    file.write(0);
}

void Project::open(const QString& path) {
    m_path = path;
    QString filePath = Utils::applicationPath(path);

    if (QFileInfo::exists(filePath)) {
        m_target = Target::Application;
        read(filePath);
        return;
    }

    filePath = Utils::libraryPath(path);

    if (QFileInfo::exists(filePath)) {
        m_target = Target::Library;
        read(filePath);
        return;
    }
}

void Project::close() {
    m_path = QString();
}

void Project::write(Format format) {
    qDebug() << "Write project file";
}

void Project::read(const QString& path) {
    qDebug() << "Read project file:" << path;
}
