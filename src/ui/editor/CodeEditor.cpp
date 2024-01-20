#include "CodeEditor.h"
#include "space/Space3d.h"
#include "node/NodeTree.h"
#include "model/NodeModel.h"
#include "external/settings/Settings.h"
#include <QtWidgets>

CodeEditor::CodeEditor(Id projectId, Settings* settings) : m_settings(settings) {
    m_nodeModel.reset(new NodeModel);

    pageComboBox = new QComboBox;
    pageComboBox->addItem(tr("3D space"));
    pageComboBox->addItem(tr("Tree"));
    pageComboBox->setCurrentIndex(settings->editor().selected);

    m_space3d = new Space3d(m_nodeModel.data(), projectId);
    m_nodeTree = new NodeTree(m_nodeModel.data());

    auto stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(m_space3d);
    stackedLayout->addWidget(m_nodeTree);
    stackedLayout->setCurrentIndex(pageComboBox->currentIndex());

    connect(pageComboBox, &QComboBox::activated, stackedLayout, &QStackedLayout::setCurrentIndex);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(pageComboBox, 0, Qt::AlignLeft);
    verticalLayout->addLayout(stackedLayout);

    setLayout(verticalLayout);
}

CodeEditor::~CodeEditor() {
    Settings::Editor editor = m_settings->editor();
    editor.selected = pageComboBox->currentIndex();

    m_settings->setEditor(editor);
}
