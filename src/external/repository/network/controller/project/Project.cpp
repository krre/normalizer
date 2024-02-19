#include "Project.h"
#include "external/repository/network/RestApi.h"

namespace Controller {

Project::Project(RestApi* restApi) : RestController(restApi) {}

QString Project::name() const {
    return "project";
}

Async::Task<Project::Response::Create> Project::create(const Request::Create& params) {
    co_return co_await RestController::create<Request::Create, Response::Create>(params);
}

Async::Task<void>Project::update(Id id, const Request::Update& params) {
    co_await RestController::update(id, params);
}

Async::Task<Project::Response::Get> Project::getOne(Id id) {
    co_return co_await RestController::getOne<Response::Get>(id);
}

Async::Task<QList<Project::Response::Get>>Project::getAll() {
    co_return co_await RestController::getAll<Response::Get>();
}

Async::Task<void>Project::remove(Id id) {
    co_await RestController::remove(id);
}

}
