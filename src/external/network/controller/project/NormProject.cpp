#include "NormProject.h"
#include "external/network/http/HttpNetwork.h"

namespace Controller {

NormProject::NormProject(HttpNetwork* network) : HttpController(network) {}

QString NormProject::name() const {
    return "project";
}

Async::Task<Id>NormProject::create(const CreateProject& project) {
    QVariant response = co_await network()->post(endpoint(), project.toJson());
    co_return response.toMap()["id"].toLongLong();
}

Async::Task<void>NormProject::update(Id id, const UpdateProject& project) {
    co_await network()->put(endpoint(id), project.toJson());
}

Async::Task<Project::GetProject> Controller::NormProject::getOne(Id id) {
    QVariant response = co_await network()->get(endpoint(id));
    co_return Project::GetProject::fromVariantMap(response.toMap());
}

Async::Task<QList<Project::GetProject>>NormProject::getAll() {
    QVariant response = co_await network()->get(endpoint());
    QList<Project::GetProject> result;

    for (const auto& item : response.toList()) {
        result.append(Project::GetProject::fromVariantMap(item.toMap()));
    }

    co_return result;
}

Async::Task<void>NormProject::remove(Id id) {
    co_await network()->deleteResource(endpoint(id));
}

}
