#include "ProjectManager.h"
#include "core/Constants.h"
#include "core/Utils.h"
#include "norm/project/Project.h"
#include "norm/expression/operator/Math.h"
#include "norm/expression/literal/NumberLiteral.h"
#include <QtCore>

ProjectManager::ProjectManager() {
}

ProjectManager::~ProjectManager() {

}

QString ProjectManager::path() const {
    return m_path;
}

Norm::Project::Target ProjectManager::target() const {
    return m_project->target();
}

void ProjectManager::create(const QString& path, Norm::Project::Target target) {
    m_project.reset(new Norm::Project);
    m_path = path;

    QString filePath;

    switch (target) {
        case Norm::Project::Target::Application:
            filePath = Utils::applicationPath(path);
            createApp();
            break;
        case Norm::Project::Target::Library:
            filePath = Utils::libraryPath(path);
            createLib();
            break;
        default: throw std::runtime_error("Unknown project target"); break;
    }

    write(filePath);
}

void ProjectManager::open(const QString& path) {
    m_project.reset(new Norm::Project);
    m_path = path;
    QString filePath = Utils::applicationPath(path) + Const::Project::Extension::Binary;

    if (QFileInfo::exists(filePath)) {
        read(filePath);
        return;
    }

    filePath = Utils::libraryPath(path) + Const::Project::Extension::Binary;

    if (QFileInfo::exists(filePath)) {
        read(filePath);
        return;
    }
}

void ProjectManager::close() {
    m_path = QString();
}

void ProjectManager::write(const QString& filePath) {
    QString binaryPath = filePath + Const::Project::Extension::Binary;
    QFile file(binaryPath);

    if (!file.open(QIODeviceBase::WriteOnly)) {
        qWarning().noquote() << "Failed to open binary file for writing:" << binaryPath;
        return;
    }

    QDataStream stream(&file);
    m_project->serialize(stream);
}

void ProjectManager::read(const QString& path) {
    QFile file(path);

    if (!file.open(QIODeviceBase::ReadOnly)) {
        qWarning().noquote() << "Failed to open binary file for reading:" << path;
        return;
    }

    QDataStream stream(&file);
    m_project->deserialize(stream);
}

void ProjectManager::createApp() {
//    auto entry = new Unit::Entry(root.data());
//    createFlow(entry->flow());
}

void ProjectManager::createLib() {
//    auto func = new Unit::Function(root.data());
//    func->setName("Add");
//    createFlow(func->flow());
}

void ProjectManager::createFlow(Norm::Flow* flow) {
//    flow->append(new Math(Math::Operation::Addition, { new Expression::NumberLiteral(3), new Expression::NumberLiteral(2) } ));
}
