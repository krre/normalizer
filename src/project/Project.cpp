#include "Project.h"
#include "Session.h"
#include "ProjectReader.h"
#include "ProjectWriter.h"
#include "ui/RenderView.h"
#include "norm/Project.h"
#include "core/Constants.h"
#include "core/Settings.h"
#include "core/Exception.h"
#include <QDir>

Project::Project(RenderView* renderView, QObject* parent) : QObject(parent), m_renderView(renderView) {
    m_session = new Session(this);
    m_opened.setBinding([&] { return !m_path.value().isEmpty(); });
}

void Project::create(const QString& name, const QString& directory, Norm::Project::Template projectTemplate) {
    QString path = directory + "/" + name;

    if (QDir(path).exists()) {
        throw ProjectExists();
    }

    close();

    QDir().mkpath(path);
    m_session->create(path);

    m_normProject.reset(new Norm::Project(name, projectTemplate));

    QString filePath = path + "/" + name + Const::Project::Extension;

    try {
        ProjectWriter writer;
        writer.write(m_normProject.get(), filePath);

        open(path);
    } catch (Exception& e) {
        qDebug() << e.error();
    }
}

void Project::open(const QString& path) {
    if (path == m_path.value()) return;

    if (!QDir(path).exists()) {
        return;
    }

    close();
    setPath(path);

    try {
        ProjectReader reader;
        m_normProject = reader.read(filePath());
    } catch (Exception& e) {
        qDebug() << e.error();
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

QString Project::filePath() const {
    QString name = QDir(m_path).dirName();
    return m_path + "/" + name + Const::Project::Extension;
}
