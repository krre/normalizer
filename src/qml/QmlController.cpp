#include "QmlController.h"
#include "external/network/RestApi.h"

namespace Qml {

RestApi* QmlController::s_restApi = nullptr;

QmlController::QmlController() {

}

void QmlController::setRestApi(RestApi* restApi) {
    s_restApi = restApi;
}

RestApi* QmlController::restApi() {
    return s_restApi;
}

}
