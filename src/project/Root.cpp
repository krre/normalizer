#include "Root.h"
#include <QJsonArray>

Root::Root() {

}

QByteArray Root::serializeToBinary() const {
    QByteArray result;

    for (auto child : children()) {
        result += static_cast<Node*>(child)->serializeToBinary();
    }

    return result;
}

QJsonValue Root::serializeToJson() const {
    QJsonArray result;

    for (auto child : children()) {
        result.append(static_cast<Node*>(child)->serializeToJson());
    }

    return result;
}
