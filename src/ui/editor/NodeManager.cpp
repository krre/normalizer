#include "NodeManager.h"
#include "external/network/RestApi.h"
#include "external/network/controller/module/Module.h"

NodeManager::NodeManager(RestApi* restApi, NodeModel* model) : m_restApi(restApi), m_model(model) {

}

NodeModel* NodeManager::model() const {
    return m_model;
}

Async::Task<void> NodeManager::createModule(Id projectId, std::optional<Id> moduleId) {
    Controller::Module module(projectId, m_restApi);
    co_await module.create();
}
