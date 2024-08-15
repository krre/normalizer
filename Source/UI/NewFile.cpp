#include "NewFile.h"
#include "ui_NewFile.h"
#include <QtWidgets>

namespace IrbisCave {

NewFile::NewFile(const QString& projectPath, QWidget* parent) :
        QDialog(parent),
        ui(new Ui::NewFile) {
    ui->setupUi(this);
    ui->lineEditLocation->setText(projectPath);
    ui->lineEditName->setFocus();
    adjustSize();
    resize(500, height());
}

NewFile::~NewFile() {
    delete ui;
}

QString NewFile::getFilePath() const {
    return filePath;
}

void NewFile::on_pushButtonBrowse_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this, QString(), ui->lineEditLocation->text());
    if (!dirPath.isEmpty()) {
        ui->lineEditLocation->setText(dirPath);
    }
}

void NewFile::on_buttonBox_accepted() {
    filePath = ui->lineEditLocation->text() + "/" + ui->lineEditName->text();
}

void NewFile::on_lineEditName_textChanged(const QString& text) {
    Q_UNUSED(text)
    changeOkButtonState();
}

void NewFile::on_lineEditLocation_textChanged(const QString& text) {
    Q_UNUSED(text)
    changeOkButtonState();
}

void NewFile::changeOkButtonState() {
    ui->buttonBox->buttons().at(0)->setEnabled(!(ui->lineEditName->text().isEmpty()
                                                  || ui->lineEditLocation->text().isEmpty()));
}

} // IrbisCave
