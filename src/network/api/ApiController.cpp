#include "ApiController.h"

namespace Api {

ApiController::ApiController(Network* network) : m_network(network) {

}

Network* ApiController::network() const {
    return m_network;
}

}
