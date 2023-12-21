#include "HttpController.h"

namespace Controller {

HttpController::HttpController(HttpNetwork* network) : m_network(network) {}

QString HttpController::endpoint() const {
    return name();
}

QString HttpController::endpoint(Id id) const {
    return QString("%1/%2").arg(name()).arg(id);
}

HttpNetwork* HttpController::network() const {
    return m_network;
}

}
