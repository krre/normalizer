#include "NetworkController.h"

namespace Controller {

NetworkController::NetworkController(NetworkManager* networkManager) : m_networkManager(networkManager) {}

NetworkManager* NetworkController::networkManager() const {
    return m_networkManager;
}

}
