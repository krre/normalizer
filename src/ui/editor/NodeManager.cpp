#include "NodeManager.h"
#include "external/network/RestApi.h"
#include "external/network/controller/module/Module.h"

NodeManager::NodeManager(Id projectId, RestApi* restApi, NodeModel* model) :
        m_projectId(projectId), m_restApi(restApi), m_model(model) {
}

NodeModel* NodeManager::model() const {
    return m_model;
}

Async::Task<void> NodeManager::getModules() {
    Controller::Module module(m_projectId, m_restApi);
    auto response = co_await module.getAll();
}

Async::Task<void> NodeManager::createModule(std::optional<Id> moduleId) {
    Controller::Module module(m_projectId, m_restApi);
    Controller::Module::CreateResponse response = co_await module.create(moduleId);
    qDebug() << response.name;
}
