#include "Module.h"
#include "external/network/RestApi.h"

namespace Controller {

Module::Module(Id projectId, RestApi* restApi) : RestController(restApi), m_projectId(projectId) {

}

QString Module::name() const {
    return QString("project/%1/module").arg(m_projectId);
}

Async::Task<Id>Module::create(std::optional<Id> moduleId) {
    CreateParams params;
    params.moduleId = moduleId;

    co_return co_await RestController::create(params);
}

Async::Task<void>Module::update(Id id, const UpdateParams& params) {
    co_await RestController::update(id, params);
}

Async::Task<Module::GetParams> Controller::Module::getOne(Id id) {
    co_return co_await RestController::getOne<GetParams>(id);
}

Async::Task<QList<Module::GetParams>>Module::getAll() {
    co_return co_await RestController::getAll<GetParams>();
}

Async::Task<void>Module::remove(Id id) {
    co_await RestController::remove(id);
}

}
