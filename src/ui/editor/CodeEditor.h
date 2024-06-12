#pragma once
#include "core/CommonTypes.h"
#include <QWidget>

class VulkanWindow;
class RestApi;
class Settings;
class View3D;
class NodeTree;
class NodeModel;
class NodeManager;

class QComboBox;
class QVulkanInstance;

class CodeEditor : public QWidget {
    Q_OBJECT
public:
    CodeEditor(Id projectId, QVulkanInstance* vulkanInstance, RestApi* restApi, Settings* settings);
    ~CodeEditor();

    Id projectId() const;

private:
    QScopedPointer<NodeManager> m_nodeManager;

    View3D* m_view3d = nullptr;
    NodeTree* m_nodeTree = nullptr;
    Settings* m_settings = nullptr;

    QComboBox* pageComboBox = nullptr;
};
