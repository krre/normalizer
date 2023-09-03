#include "Project.h"

namespace Norm {

Project::Project(const QString& name, Template projectTemplate) : m_name(name), m_projectTemplate(projectTemplate) {

}

void Project::setName(const QString& name) {
    m_name = name;
}

QString Project::name() const {
    return m_name;
}

Project::Template Project::projectTemplate() const {
    return m_projectTemplate;
}

void Project::getSerializedProperties(QDataStream& stream) const {
}

void Project::setParsedProperties(const QDataStream& stream) {
}

}
