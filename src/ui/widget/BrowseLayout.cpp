#include "BrowseLayout.h"
#include <QtWidgets>

BrowseLayout::BrowseLayout(const QString& text) {
    m_lineEdit = new QLineEdit(text);

    auto pushButton = new QPushButton(tr("Browse..."));
    connect(pushButton, &QPushButton::clicked, this, &BrowseLayout::onClicked);

    addWidget(m_lineEdit);
    addWidget(pushButton);
}

QString BrowseLayout::text() const {
    return m_lineEdit->text();
}

void BrowseLayout::setFocus() {
    m_lineEdit->setFocus();
}

void BrowseLayout::setWidgetsEnabled(bool enable) {
    for (int i = 0; i < count(); i++) {
        itemAt(i)->widget()->setEnabled(enable);
    }
}

void BrowseLayout::onClicked() {
    QString dirPath = QFileDialog::getExistingDirectory();

    if (!dirPath.isEmpty()) {
        m_lineEdit->setText(dirPath);
    }
}
