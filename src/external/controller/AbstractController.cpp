#include "AbstractController.h"
#include "external/repository/Repository.h"

namespace Controller {

AbstractController::AbstractController(Repository* repository) : m_repository(repository) {}

}
