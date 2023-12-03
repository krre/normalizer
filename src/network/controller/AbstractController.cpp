#include "AbstractController.h"

namespace Controller {

AbstractController::AbstractController(NetworkManager* networkManager) : m_networkManager(networkManager) {}

NetworkManager* AbstractController::networkManager() const {
    return m_networkManager;
}

}
