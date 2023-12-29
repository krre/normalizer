#include "View.h"
#include "RenderView.h"
#include "TreeView.h"
#include "settings/Settings.h"
#include <QtWidgets>

View::View(const QUrl& editorUrl, Id projectId, Settings* settings) : m_settings(settings) {
    pageComboBox = new QComboBox;
    pageComboBox->addItem(tr("3D space"));
    pageComboBox->addItem(tr("Tree"));
    pageComboBox->setCurrentIndex(settings->view().selected);

    m_renderView = new RenderView(editorUrl, projectId);
    m_treeView = new TreeView();

    auto stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(m_renderView);
    stackedLayout->addWidget(m_treeView);
    stackedLayout->setCurrentIndex(pageComboBox->currentIndex());

    connect(pageComboBox, &QComboBox::activated, stackedLayout, &QStackedLayout::setCurrentIndex);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(pageComboBox, 0, Qt::AlignLeft);
    verticalLayout->addLayout(stackedLayout);

    setLayout(verticalLayout);
}

View::~View() {
    Settings::View view = m_settings->view();
    view.selected = pageComboBox->currentIndex();

    m_settings->setView(view);
}
