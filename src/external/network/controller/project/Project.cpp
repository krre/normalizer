#include "Project.h"
#include "external/network/RestApi.h"

namespace Controller {

Project::Project(RestApi* restApi) : RestController(restApi) {}

QString Project::name() const {
    return "project";
}

Async::Task<Id>Project::create(const CreateParams& params) {
    co_return co_await RestController::create(params);
}

Async::Task<void>Project::update(Id id, const UpdateParams& params) {
    co_await RestController::update(id, params);
}

Async::Task<Project::GetParams> Controller::Project::getOne(Id id) {
    co_return co_await RestController::getOne<GetParams>(id);
}

Async::Task<QList<Project::GetParams>>Project::getAll() {
co_return co_await RestController::getAll<GetParams>();
}

Async::Task<void>Project::remove(Id id) {
    co_await RestController::remove(id);
}

}
