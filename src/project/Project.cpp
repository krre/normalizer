#include "Project.h"
#include "ProjectSettings.h"
#include "Root.h"
#include "Node.h"
#include "core/Global.h"
#include "core/Utils.h"
#include "norm/unit/Entry.h"
#include "norm/unit/Flow.h"
#include "norm/expression/operator/Math.h"
#include "norm/expression/literal/NumberLiteral.h"
#include <QtCore>

Project::Project() {
    root.reset(new Root);
}

Project::~Project() {

}

QString Project::path() const {
    return m_path;
}

Project::Target Project::target() const {
    return m_target;
}

void Project::create(const QString& path, Target target) {
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

void Project::write(const QString& filePath) {
    qDebug() << root->serializeToJson();

    QFile file(filePath);

    if (!file.open(QIODeviceBase::WriteOnly)) {
        qWarning().noquote() << "Failed to open project file for writing:" << filePath;
        return;
    }

    file.write(0);
}

void Project::read(const QString& path) {
    root.reset(new Root);
    qDebug() << "Read project file:" << path;
}

void Project::createApp() {
    auto entry = new Unit::Entry(root.data());
    createFlow(entry->flow());
}

void Project::createLib() {
    auto func = new Unit::Function(root.data());
    func->setName("Add");
    createFlow(func->flow());
}

void Project::createFlow(Unit::Flow* flow) {
    using namespace Expression::Operator;
    flow->append(new Math(Math::Operation::Addition, { new Expression::NumberLiteral(3), new Expression::NumberLiteral(2) } ));
}
