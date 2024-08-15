#pragma once
#include "core/CommonTypes.h"
#include <QWidget>

class VulkanWindow;
class RestApi;
class Settings;
class View3D;
class NodeTree;
class NodeModel;
class Repository;

class QComboBox;
class QVulkanInstance;

class CodeEditor : public QWidget {
    Q_OBJECT
public:
    CodeEditor(Id projectId, QVulkanInstance* vulkanInstance, RestApi* restApi, Settings* settings);
    ~CodeEditor();

    Id projectId() const;

private:
    QScopedPointer<Repository> m_nodeManager;

    View3D* m_view3d = nullptr;
    Settings* m_settings = nullptr;
};
