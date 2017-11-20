#include "NewProject.h"
#include "ui_NewProject.h"
#include "Core/Settings.h"
#include "Core/Defines.h"
#include <QtWidgets>

NewProject::NewProject(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::NewProject) {
    _ui->setupUi(this);
    adjustSize();
    resize(500, height());
    _ui->lineEditLocation->setText(Settings::instance()->readWorkspace());
    _ui->lineEditName->setFocus();
}

NewProject::~NewProject() {
    delete _ui;
}

QString NewProject::projectPath() const {
    return _projectPath;
}

void NewProject::on_pushButtonBrowse_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (!dirPath.isEmpty()) {
        _ui->lineEditLocation->setText(dirPath);
    }
}

void NewProject::on_buttonBox_accepted() {
    QString projectPath = _ui->lineEditLocation->text() + "/" + _ui->lineEditName->text();
    QDir dir;
    if (dir.mkpath(projectPath)) {
        _projectPath = projectPath;
        dir.cd(projectPath);
        dir.mkdir(PROJECT_DIRECTORY);
        dir.mkdir(PROJECT_BUILD_DIRECTORY);
    } else {
        qDebug() << "Error creating project directory" << projectPath; // TODO: Make message dialog
    }
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
