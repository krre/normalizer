#include "SelectWorkspace.h"
#include "ui_SelectWorkspace.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtWidgets>

namespace IrbisCave {

SelectWorkspace::SelectWorkspace(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SelectWorkspace) {
    ui->setupUi(this);
    setWindowTitle(APP_NAME);
    adjustSize();
    resize(400, height());
    ui->lineEdit->setText(QDir::homePath() + "/" + WORKSPACE_DIRECTORY);
}

SelectWorkspace::~SelectWorkspace() {
    delete ui;
}

bool SelectWorkspace::getIsRejected() const {
    return isRejected;
}

void SelectWorkspace::on_pushButtonBrowse_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (!dirPath.isEmpty()) {
        ui->lineEdit->setText(dirPath);
    }
}

void SelectWorkspace::on_buttonBox_accepted() {
    Settings::instance()->setValue("Path/workspace", ui->lineEdit->text());
}

void SelectWorkspace::on_buttonBox_rejected() {
    isRejected = true;
}

void SelectWorkspace::on_lineEdit_textChanged(const QString& text) {
    ui->buttonBox->buttons().at(0)->setEnabled(!text.isEmpty());
}

} // IrbisCave
