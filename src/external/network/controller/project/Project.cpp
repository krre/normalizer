#include "Project.h"
#include "external/network/RestApi.h"

namespace Controller {

Project::Project(RestApi* restApi) : RestController(restApi) {}

QString Project::name() const {
    return "project";
}

Async::Task<Id>Project::create(const CreateProject& project) {
    QVariant response = co_await restApi()->post(endpoint(), project.serialize());
    co_return response.toMap()["id"].toLongLong();
}

Async::Task<void>Project::update(Id id, const UpdateProject& project) {
    co_await restApi()->put(endpoint(id), project.serialize());
}

Async::Task<Project::GetProject> Controller::Project::getOne(Id id) {
    QVariant response = co_await restApi()->get(endpoint(id));
    co_return Project::GetProject::parse(response);
}

Async::Task<QList<Project::GetProject>>Project::getAll() {
    QVariant response = co_await restApi()->get(endpoint());
    QList<Project::GetProject> result;

    for (const auto& item : response.toList()) {
        result.append(Project::GetProject::parse(item));
    }

    co_return result;
}

Async::Task<void>Project::remove(Id id) {
    co_await restApi()->del(endpoint(id));
}

}
