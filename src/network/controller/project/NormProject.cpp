#include "NormProject.h"
#include "network/http/HttpNetwork.h"

namespace Controller {

NormProject::NormProject(HttpNetwork* network) : HttpController(network) {}

QString NormProject::name() const {
    return "project";
}

Async::Task<Id>NormProject::create(const CreateProject& project) {
    QVariant response = co_await network()->post(name(), project.toJson());
    co_return response.toMap()["id"].toLongLong();
}

Async::Task<void>NormProject::update(Id id, const UpdateProject& project) {
    co_await network()->put(QString("%1/%2").arg(name()).arg(id), project.toJson());
}

Async::Task<Project::GetProject> Controller::NormProject::getOne(Id id) {
    QVariant response = co_await network()->get(QString("%1/%2").arg(name()).arg(id));
    co_return Project::GetProject::fromVariantMap(response.toMap());
}

Async::Task<QList<Project::GetProject>>NormProject::getList() {
    QVariant response = co_await network()->get(name());
    QList<Project::GetProject> result;

    for (const auto& item : response.toList()) {
        result.append(Project::GetProject::fromVariantMap(item.toMap()));
    }

    co_return result;
}

Async::Task<void>NormProject::remove(Id id) {
    co_await network()->deleteResource(QString("%1/%2").arg(name()).arg(id));
}

}
