#pragma once

class RestApi;
class NodeModel;

class NodeManager {
public:
    NodeManager(RestApi* restApi, NodeModel* model);

    NodeModel* model() const;

private:
    RestApi* m_restApi = nullptr;
    NodeModel* m_model = nullptr;
};
