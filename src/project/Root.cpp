#include "Root.h"
#include <QJsonArray>

Root::Root() {

}

QJsonValue Root::serializeToJson() const {
    QJsonArray result;

    for (auto child : children()) {
        result.append(static_cast<Node*>(child)->serializeToJson());
    }

    return result;
}
