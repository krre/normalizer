#include "CodeEditor.h"
#include "NodeManager.h"
#include "3d/View3D.h"
#include "external/settings/Settings.h"
#include "gfx/VulkanWindow.h"
#include <QtWidgets>

CodeEditor::CodeEditor(Id projectId, QVulkanInstance* vulkanInstance, RestApi* restApi, Settings* settings) : m_settings(settings) {
    m_nodeManager.reset(new NodeManager(projectId, restApi));
    m_view3d = new View3D(new VulkanWindow(vulkanInstance), m_nodeManager.data());

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(QMargins());
    verticalLayout->addWidget(m_view3d);

    setLayout(verticalLayout);

    m_nodeManager->getModules();
}

CodeEditor::~CodeEditor() {
}

Id CodeEditor::projectId() const {
    return m_nodeManager->projectId();
}
