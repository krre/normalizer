#include "NodeManager.h"
#include "external/network/RestApi.h"

NodeManager::NodeManager(RestApi* restApi, NodeModel* model) : m_restApi(restApi), m_model(model) {

}

NodeModel* NodeManager::model() const {
    return m_model;
}
