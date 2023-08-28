#include "Project.h"

constexpr auto binaryTemplate = "bin";
constexpr auto libraryTemplate = "lib";

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

void Project::getSerializedProperties(SerializedProperties& properties) const {
    properties.append("name", m_name);
    properties.append("template", m_projectTemplate == Template::Binary ? binaryTemplate : libraryTemplate);
}

void Project::setParsedProperties(ParsedProperties& properties) {
    m_name = properties.value("name").toString();
    m_projectTemplate = properties.value("template").toString() == binaryTemplate ? Template::Binary : Template::Library;
}

}
