#include "View.h"
#include "RenderView.h"
#include "TreeView.h"
#include <QtWidgets>

View::View(const QUrl& editorUrl, Id projectId) {
    auto pageComboBox = new QComboBox;
    pageComboBox->addItem(tr("3D space"));
    pageComboBox->addItem(tr("Tree"));

    m_renderView = new RenderView(editorUrl, projectId);
    m_treeView = new TreeView();

    auto stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(m_renderView);
    stackedLayout->addWidget(m_treeView);

    connect(pageComboBox, &QComboBox::activated, stackedLayout, &QStackedLayout::setCurrentIndex);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(pageComboBox, 0, Qt::AlignLeft);
    verticalLayout->addLayout(stackedLayout);

    setLayout(verticalLayout);
}
