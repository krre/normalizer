#include "BrowseLayout.h"
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

BrowseLayout::BrowseLayout(const QString& dir) {
    m_lineEdit = new QLineEdit(dir);

    auto pushButton = new QPushButton(tr("Browse..."));
    connect(pushButton, &QPushButton::clicked, this, &BrowseLayout::onClicked);

    addWidget(m_lineEdit);
    addWidget(pushButton);
}

QLineEdit* BrowseLayout::lineEdit() const {
    return m_lineEdit;
}

void BrowseLayout::onClicked() {
    QString dirPath = QFileDialog::getExistingDirectory(nullptr, QString(), m_lineEdit->text());

    if (!dirPath.isEmpty()) {
        m_lineEdit->setText(dirPath);
    }
}
