#include "RestController.h"

namespace Controller {

RestController::RestController(HttpNetwork* network) : m_network(network) {}

QString RestController::endpoint() const {
    return name();
}

QString RestController::endpoint(Id id) const {
    return QString("%1/%2").arg(name()).arg(id);
}

HttpNetwork* RestController::network() const {
    return m_network;
}

}
