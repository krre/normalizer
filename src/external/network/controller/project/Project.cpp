#include "Project.h"
#include "external/network/RestApi.h"

namespace Controller {

Project::Project(RestApi* restApi) : RestController(restApi) {}

QString Project::name() const {
    return "project";
}

Async::Task<Project::CreateResponse> Project::create(const CreateRequest& params) {
    co_return co_await RestController::create<CreateRequest, CreateResponse>(params);
}

Async::Task<void>Project::update(Id id, const UpdateRequest& params) {
    co_await RestController::update(id, params);
}

Async::Task<Project::GetResponse> Controller::Project::getOne(Id id) {
    co_return co_await RestController::getOne<GetResponse>(id);
}

Async::Task<QList<Project::GetResponse>>Project::getAll() {
    co_return co_await RestController::getAll<GetResponse>();
}

Async::Task<void>Project::remove(Id id) {
    co_await RestController::remove(id);
}

}
