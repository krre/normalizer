#include "Project.h"
#include <QDataStream>

namespace Norm {

Project::Project() {

}

Project::~Project() {

}

Token::Type Project::type() const {
    return Type::Porject;
}

void Project::serialize(QDataStream& stream) const {
    Token::serialize(stream);
    stream << quint8(m_target);
}

void Project::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
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
