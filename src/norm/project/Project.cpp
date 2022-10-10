#include "Project.h"

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
}

void Project::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
}

}
