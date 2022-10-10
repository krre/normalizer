#include "ProjectManager.h"
#include "Root.h"
#include "Node.h"
#include "core/Constants.h"
#include "core/Global.h"
#include "core/Utils.h"
#include "norm/Header.h"
#include "norm/unit/Entry.h"
#include "norm/unit/Flow.h"
#include "norm/expression/operator/Math.h"
#include "norm/expression/literal/NumberLiteral.h"
#include <QtCore>

ProjectManager::ProjectManager() {
    header.reset(new Norm::Header);
    root.reset(new Root);
}

ProjectManager::~ProjectManager() {

}

QString ProjectManager::path() const {
    return m_path;
}

ProjectManager::Target ProjectManager::target() const {
    return m_target;
}

void ProjectManager::create(const QString& path, Target target) {
    m_path = path;

    header.reset(new Norm::Header);
    header->setVersion(Global::Version::language());

    root.reset(new Root);

    QString filePath;

    switch (target) {
        case Target::Application:
            filePath = Utils::applicationPath(path);
            createApp();
            break;
        case Target::Library:
            filePath = Utils::libraryPath(path);
            createLib();
            break;
        default: throw std::runtime_error("Unknown project target"); break;
    }

    write(filePath);
}

void ProjectManager::open(const QString& path) {
    m_path = path;
    QString filePath = Utils::applicationPath(path) + Const::Project::Extension::Binary;

    if (QFileInfo::exists(filePath)) {
        m_target = Target::Application;
        read(filePath);
        return;
    }

    filePath = Utils::libraryPath(path) + Const::Project::Extension::Binary;

    if (QFileInfo::exists(filePath)) {
        m_target = Target::Library;
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
    header->serialize(stream);
}

void ProjectManager::read(const QString& path) {
    QFile file(path);

    if (!file.open(QIODeviceBase::ReadOnly)) {
        qWarning().noquote() << "Failed to open binary file for readin:" << path;
        return;
    }

    QDataStream stream(&file);

    header.reset(new Norm::Header);
    header->deserialize(stream);

    root.reset(new Root);
}

void ProjectManager::createApp() {
    auto entry = new Unit::Entry(root.data());
    createFlow(entry->flow());
}

void ProjectManager::createLib() {
    auto func = new Unit::Function(root.data());
    func->setName("Add");
    createFlow(func->flow());
}

void ProjectManager::createFlow(Unit::Flow* flow) {
    using namespace Expression::Operator;
    flow->append(new Math(Math::Operation::Addition, { new Expression::NumberLiteral(3), new Expression::NumberLiteral(2) } ));
}
