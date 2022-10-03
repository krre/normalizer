#include "Entry.h"

namespace Unit {

Entry::Entry(Node* parent) : Function(parent) {
    setName("Entry");
}

QJsonValue Entry::serializeToJson() const {
    return Function::serializeToJson();
}

}
