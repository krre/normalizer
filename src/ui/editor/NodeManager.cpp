#include "NodeManager.h"
#include "model/NodeModel.h"
#include "external/network/RestApi.h"
#include "external/network/controller/module/Module.h"

NodeManager::NodeManager(Id projectId, RestApi* restApi) : m_projectId(projectId), m_restApi(restApi) {
}

NodeManager::~NodeManager() {

}

NodeModel* NodeManager::model() const {
    return m_model.data();
}

Id NodeManager::projectId() const {
    return m_projectId;
}

Async::Task<void> NodeManager::getModules() {
    Controller::Module module(m_projectId, m_restApi);
    auto response = co_await module.getAll();
}

Async::Task<void> NodeManager::createModule(std::optional<Id> moduleId) {
    Controller::Module module(m_projectId, m_restApi);
    auto response = co_await module.create(moduleId);
    qDebug() << response.name;
}
