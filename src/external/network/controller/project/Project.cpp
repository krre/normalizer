#include "Project.h"
#include "external/network/RestApi.h"

namespace Controller {

Project::Project(RestApi* restApi) : RestController(restApi) {}

QString Project::name() const {
    return "project";
}

Async::Task<Id>Project::create(const CreateProject& project) {
    co_return co_await RestController::create(project);
}

Async::Task<void>Project::update(Id id, const UpdateProject& project) {
    co_await RestController::update(id, project);
}

Async::Task<Project::GetProject> Controller::Project::getOne(Id id) {
    co_return co_await RestController::getOne<Project::GetProject>(id);
}

Async::Task<QList<Project::GetProject>>Project::getAll() {
co_return co_await RestController::getAll<Project::GetProject>();
}

Async::Task<void>Project::remove(Id id) {
    co_await RestController::remove(id);
}

}
