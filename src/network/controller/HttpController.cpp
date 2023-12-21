#include "HttpController.h"

namespace Controller {

HttpController::HttpController(HttpNetwork* network) : m_network(network) {}

HttpNetwork* HttpController::network() const {
    return m_network;
}

}
