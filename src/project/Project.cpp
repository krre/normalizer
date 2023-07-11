#include "Project.h"
#include "Session.h"
#include "ui/RenderView.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include <norm/token/project/BinaryProject.h>
#include <norm/token/project/LibraryProject.h>
#include <norm/token/Function.h>
#include <QDir>

Project::Project(RenderView* renderView, QObject* parent) : QObject(parent), m_renderView(renderView) {
    m_session = new Session(this);
    m_opened.setBinding([&] { return !m_path.value().isEmpty(); });
}

void Project::create(const QString& name, const QString& directory, Template projectTemplate) {
    QString path = directory + "/" + name;

    if (QDir(path).exists()) {
        throw ProjectExists();
    }

    close();

    QDir().mkpath(path);
    m_session->create(path);

    QString filePath = path + "/" + name + Const::Project::Extension;

    if (projectTemplate == Template::Binary) {
        createBinary(name, filePath);
    } else {
        createLibrary(name, filePath);
    }

    open(path);
}

void Project::open(const QString& path) {
    if (path == m_path.value()) return;

    if (!QDir(path).exists()) {
        return;
    }

    close();
    setPath(path);

    QString name = QDir(path).dirName();
    QString filePath = path + "/" + name + Const::Project::Extension;

    try {
        auto project = Norm::Project::read(filePath.toStdString());
        m_project.reset(project);
    } catch (std::exception& e) {
        qDebug() << e.what();
    }
}

void Project::save() {

}

void Project::close() {
    setPath("");
}

void Project::setPath(const QString& path) {
    m_path = path;
    m_renderView->setVisible(!path.isEmpty());
    Settings::setValue<General::LastProject>(m_path);
}

void Project::createBinary(const QString& name, const QString& filePath) {
    Norm::BinaryProject project(name.toStdString());
    project.write(filePath.toStdString());
}

void Project::createLibrary(const QString& name, const QString& filePath) {
    Norm::LibraryProject project(name.toStdString());
    project.write(filePath.toStdString());
}
