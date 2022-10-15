#include "Project.h"
#include <QDataStream>
#include "core/Constants.h"

namespace Norm {

Project::Project() {

}

Project::~Project() {

}

Code Project::code() const {
    return Const::Norm::Token::Project;
}

void Project::serialize(QDataStream& stream) const {
    Token::serialize(stream);
    NameId::serialize(stream);
    stream << quint8(m_target);
}

void Project::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
    NameId::deserialize(stream);

    quint8 t;
    stream >> t;
    m_target = Target(t);
}

Project::Target Project::target() const {
    return m_target;
}

void Project::setTarget(Target target) {
    m_target = target;
}

}
