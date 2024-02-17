#include "Module.h"
#include "external/repository/network/RestApi.h"

namespace Controller {

Module::Module(Id projectId, RestApi* restApi) : RestController(restApi), m_projectId(projectId) {

}

QString Module::name() const {
    return QString("project/%1/module").arg(m_projectId);
}

Async::Task<Module::CreateResponse> Module::create(std::optional<Id> moduleId) {
    CreateRequest params;
    params.moduleId = moduleId;

    co_return co_await RestController::create<CreateRequest, CreateResponse>(params);
}

Async::Task<void>Module::update(Id id, const UpdateRequest& params) {
    co_await RestController::update(id, params);
}

Async::Task<Module::GetResponse> Module::getOne(Id id) {
    co_return co_await RestController::getOne<GetResponse>(id);
}

Async::Task<QList<Module::GetResponse>>Module::getAll() {
    co_return co_await RestController::getAll<GetResponse>();
}

Async::Task<void>Module::remove(Id id) {
    co_await RestController::remove(id);
}

}
