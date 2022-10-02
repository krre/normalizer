#include "Entry.h"

namespace Unit {

Entry::Entry(Node* parent) : Function(parent) {

}

QJsonValue Entry::serializeToJson() const {
    return Function::serializeToJson();
}

}
