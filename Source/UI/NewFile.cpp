#include "NewFile.h"
#include "ui_NewFile.h"
#include <QtWidgets>

NewFile::NewFile(const QString& projectPath, QWidget* parent) :
        QDialog(parent),
        _ui(new Ui::NewFile) {
    _ui->setupUi(this);
    _ui->lineEditLocation->setText(projectPath);
    _ui->lineEditName->setFocus();
    adjustSize();
    resize(500, height());
}

NewFile::~NewFile() {
    delete _ui;
}

QString NewFile::filePath() const {
    return _filePath;
}

void NewFile::on_pushButtonBrowse_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this, QString(), _ui->lineEditLocation->text());
    if (!dirPath.isEmpty()) {
        _ui->lineEditLocation->setText(dirPath);
    }
}

void NewFile::on_buttonBox_accepted() {
    _filePath = _ui->lineEditLocation->text() + "/" + _ui->lineEditName->text();
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
    _ui->buttonBox->buttons().at(0)->setEnabled(!(_ui->lineEditName->text().isEmpty()
                                                  || _ui->lineEditLocation->text().isEmpty()));
}
