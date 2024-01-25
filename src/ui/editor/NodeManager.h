#pragma once
#include "core/async/Task.h"
#include "core/CommonTypes.h"

class RestApi;
class NodeModel;

class NodeManager {
public:
    NodeManager(Id projectId, RestApi* restApi, NodeModel* model);

    NodeModel* model() const;

    Async::Task<void> getModules();
    Async::Task<void> createModule(std::optional<Id> moduleId = std::nullopt);

private:
    Id m_projectId = 0;
    RestApi* m_restApi = nullptr;
    NodeModel* m_model = nullptr;
};
