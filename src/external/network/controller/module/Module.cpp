#include "Module.h"
#include "external/network/RestApi.h"
#include "external/network/controller/project/Project.h"

namespace Controller {

Module::Module(Id projectId, RestApi* restApi) : RestController(restApi), m_projectId(projectId) {

}

QString Module::name() const {
    return QString("%1/%2/%3").arg(Project::Name).arg(m_projectId).arg(Name);
}

Async::Task<Module::Response::Create> Module::create(std::optional<Id> moduleId) {
    Request::Create params;
    params.moduleId = moduleId;

    co_return co_await RestController::create<Request::Create, Response::Create>(params);
}

Async::Task<void> Module::update(Id id, const Request::Update& params) {
    co_await RestController::update(id, params);
}

Async::Task<Module::Response::Get> Module::getOne(Id id) {
    co_return co_await RestController::getOne<Response::Get>(id);
}

Async::Task<QList<Module::Response::Get>> Module::getAll() {
    co_return co_await RestController::getAll<Response::Get>();
}

Async::Task<void> Module::remove(Id id) {
    co_await RestController::remove(id);
}

}
