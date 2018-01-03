#include "NewProject.h"
#include "ui_NewProject.h"
#include "Core/Settings.h"
#include "Core/Defines.h"
#include <QtWidgets>

namespace IrbisCave {

NewProject::NewProject(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::NewProject) {
    ui->setupUi(this);
    adjustSize();
    resize(500, height());
    ui->lineEditLocation->setText(Settings::instance()->readWorkspace());
    ui->lineEditName->setFocus();
}

NewProject::~NewProject() {
    delete ui;
}

QString NewProject::projectPath() const {
    return m_projectPath;
}

void NewProject::on_pushButtonBrowse_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (!dirPath.isEmpty()) {
        ui->lineEditLocation->setText(dirPath);
    }
}

void NewProject::on_buttonBox_accepted() {
    QString projectPath = ui->lineEditLocation->text() + "/" + ui->lineEditName->text();
    QDir dir;
    if (dir.mkpath(projectPath)) {
        m_projectPath = projectPath;
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
    ui->buttonBox->buttons().at(0)->setEnabled(!(ui->lineEditName->text().isEmpty()
                                                  || ui->lineEditLocation->text().isEmpty()));
}

} // IrbisCave
