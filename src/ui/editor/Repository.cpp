#include "Repository.h"
#include "external/network/RestApi.h"
#include "external/network/controller/module/Module.h"

Repository::Repository(Id projectId, RestApi* restApi) : m_projectId(projectId), m_restApi(restApi) {
}

Repository::~Repository() {

}

Id Repository::projectId() const {
    return m_projectId;
}

Async::Task<void> Repository::getModules() {
    Controller::Module module(m_projectId, m_restApi);
    auto response = co_await module.getAll();
}

Async::Task<void> Repository::createModule(std::optional<Id> moduleId) {
    Controller::Module module(m_projectId, m_restApi);
    auto response = co_await module.create(moduleId);
    qDebug() << response.name;
}
