#include "BrowseLineEdit.h"
#include <QtWidgets>

BrowseLineEdit::BrowseLineEdit(const QString& text) {
    lineEdit = new QLineEdit(text);
    connect(lineEdit, &QLineEdit::textChanged, this, &BrowseLineEdit::textChanged);

    auto browseButton = new QPushButton(tr("Browse..."));
    connect(browseButton, &QPushButton::clicked, this, &BrowseLineEdit::onBrowseClicked);

    addWidget(lineEdit);
    addWidget(browseButton);
}

QString BrowseLineEdit::text() const {
    return lineEdit->text();
}

void BrowseLineEdit::setText(const QString& text) {
    lineEdit->setText(text);
}

void BrowseLineEdit::onBrowseClicked() {
    QFileInfo fi(lineEdit->text());
    QString dirPath = QFileDialog::getExistingDirectory(nullptr, tr("Select Directory"), fi.dir().path());

    if (!dirPath.isEmpty()) {
        lineEdit->setText(dirPath);
    }
}
