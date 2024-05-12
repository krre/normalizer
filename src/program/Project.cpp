#include "Project.h"

Project::Project(Target target, Location location, const QString& name, const QString& description)
    : m_target(target), m_location(location), m_name(name), m_description(description) {

}
