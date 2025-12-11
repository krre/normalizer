#include "ApiController.h"

namespace Api {

ApiController::ApiController(ApiNetwork* network) : m_network(network) {

}

ApiNetwork* ApiController::network() const {
    return m_network;
}

}
