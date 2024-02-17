#include "RestController.h"

namespace Controller {

RestController::RestController(RestApi* restApi) : m_restApi(restApi) {}

QString RestController::endpoint() const {
    return name();
}

QString RestController::endpoint(Id id) const {
    return QString("%1/%2").arg(name()).arg(id);
}

RestApi* RestController::restApi() const {
    return m_restApi;
}

Async::Task<void> RestController::remove(Id id) {
    co_await m_restApi->del(endpoint(id));
}

}
