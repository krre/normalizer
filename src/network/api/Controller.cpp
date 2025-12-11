#include "Controller.h"

namespace Api {

Controller::Controller(Network* network) : m_network(network) {

}

Network* Controller::network() const {
    return m_network;
}

}
