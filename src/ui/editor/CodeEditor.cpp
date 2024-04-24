#include "CodeEditor.h"
#include "NodeManager.h"
#include "3d/View3D.h"
#include "tree/NodeTree.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

CodeEditor::CodeEditor(Id projectId, RestApi* restApi, Settings* settings) : m_settings(settings) {
    m_nodeManager.reset(new NodeManager(projectId, restApi));

    pageComboBox = new QComboBox;
    pageComboBox->addItem(tr("3D View"));
    pageComboBox->addItem(tr("Node Tree"));
    pageComboBox->setCurrentIndex(settings->editor().selected);

    m_view3d = new View3D(m_nodeManager.data());
    m_nodeTree = new NodeTree(m_nodeManager.data());

    auto stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(m_view3d);
    stackedLayout->addWidget(m_nodeTree);
    stackedLayout->setCurrentIndex(pageComboBox->currentIndex());

    connect(pageComboBox, &QComboBox::activated, stackedLayout, &QStackedLayout::setCurrentIndex);

    QToolBar* toolBar = new QToolBar;
    toolBar->addWidget(pageComboBox);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(QMargins());
    verticalLayout->setSpacing(0);
    verticalLayout->addWidget(toolBar);
    verticalLayout->addLayout(stackedLayout);

    setLayout(verticalLayout);

    m_nodeManager->getModules();
}

CodeEditor::~CodeEditor() {
    Settings::Editor editor = m_settings->editor();
    editor.selected = pageComboBox->currentIndex();

    m_settings->setEditor(editor);
}

Id CodeEditor::projectId() const {
    return m_nodeManager->projectId();
}
