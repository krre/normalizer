#include "SelectWorkspace.h"
#include "ui_SelectWorkspace.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>

SelectWorkspace::SelectWorkspace(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::SelectWorkspace) {
    _ui->setupUi(this);
    setWindowTitle(APP_NAME);
    adjustSize();
    resize(400, height());
    _ui->lineEdit->setText(QDir::homePath() + "/" + WORKSPACE_DIRECTORY);
}

SelectWorkspace::~SelectWorkspace() {
    delete _ui;
}

bool SelectWorkspace::isRejected() const {
    return _isRejected;
}

void SelectWorkspace::on_pushButtonBrowse_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (!dirPath.isEmpty()) {
        _ui->lineEdit->setText(dirPath);
    }
}

void SelectWorkspace::on_buttonBox_accepted() {
    Settings::instance()->setValue("Path/workspace", _ui->lineEdit->text());
}

void SelectWorkspace::on_buttonBox_rejected() {
    _isRejected = true;
}

void SelectWorkspace::on_lineEdit_textChanged(const QString& text) {
    _ui->buttonBox->buttons().at(0)->setEnabled(!text.isEmpty());
}
