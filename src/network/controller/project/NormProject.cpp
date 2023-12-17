#include "NormProject.h"
#include "network/http/HttpNetwork.h"

namespace Controller {

NormProject::NormProject(HttpNetwork* httpNetwork) : m_httpNetwork(httpNetwork) {}

Async::Task<Id>NormProject::create(const CreateProject& project) {
    QVariant response = co_await m_httpNetwork->post(NAME, project.toJson());
    co_return response.toMap()["id"].toLongLong();
}

Async::Task<void>NormProject::update(Id id, const UpdateProject& project) {
    co_await m_httpNetwork->put(QString("%1/%2").arg(NAME).arg(id), project.toJson());
}

Async::Task<Project::GetProject> Controller::NormProject::getOne(Id id) {
    QUrlQuery query = { { "id", QString::number(id) } };
    QVariant response = co_await m_httpNetwork->get(NAME, query);
    co_return Project::GetProject::fromVariantMap(response.toMap());
}

Async::Task<QList<Project::GetProject>>NormProject::getList() {
    QVariant response = co_await m_httpNetwork->get(NAME);
    QList<Project::GetProject> result;

    for (const auto& item : response.toList()) {
        result.append(Project::GetProject::fromVariantMap(item.toMap()));
    }

    co_return result;
}

Async::Task<void>NormProject::remove(Id id) {
    co_await m_httpNetwork->deleteResource(QString("%1/%2").arg(NAME).arg(id));
}

}
