#pragma once
#include "core/async/Task.h"
#include "core/CommonTypes.h"

class RestApi;
class NodeModel;

class NodeManager {
public:
    NodeManager(RestApi* restApi, NodeModel* model);

    NodeModel* model() const;

    Async::Task<void> createModule(Id projectId, std::optional<Id> moduleId = std::nullopt);

private:
    RestApi* m_restApi = nullptr;
    NodeModel* m_model = nullptr;
};
