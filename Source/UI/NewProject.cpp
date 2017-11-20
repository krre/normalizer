#include "NewProject.h"
#include "ui_NewProject.h"
#include "Core/Settings.h"
#include <QtWidgets>

NewProject::NewProject(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::NewProject) {
    _ui->setupUi(this);
    adjustSize();
    resize(500, height());
    _ui->lineEditLocation->setText(Settings::instance()->readWorkspace());
}

NewProject::~NewProject() {
    delete _ui;
}

void NewProject::on_pushButtonBrowse_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (!dirPath.isEmpty()) {
        _ui->lineEditLocation->setText(dirPath);
    }
}

void NewProject::on_buttonBox_accepted() {
    QString projectPath = _ui->lineEditLocation->text() + "/" + _ui->lineEditName->text();
    qDebug() << projectPath;
}

void NewProject::on_lineEditName_textChanged(const QString& text) {
    Q_UNUSED(text)
    changeOkButtonState();
}

void NewProject::on_lineEditLocation_textChanged(const QString& text) {
    Q_UNUSED(text)
    changeOkButtonState();
}

void NewProject::changeOkButtonState() {
    _ui->buttonBox->buttons().at(0)->setEnabled(!(_ui->lineEditName->text().isEmpty()
                                                  || _ui->lineEditLocation->text().isEmpty()));
}
