#include "Options.h"
#include "ui_Options.h"
#include "../Defines.h"
#include <QtCore>
#include <QtWidgets>

Options::Options(QWidget* parent) :
        QDialog(parent),
        ui(new Ui::Options),
        settings(QCoreApplication::applicationDirPath() + "/" + SETTINGS_NAME, QSettings::IniFormat) {
    ui->setupUi(this);
    adjustSize();
    resize(500, height());
    readSettings();
}

Options::~Options() {
    delete ui;
}

void Options::on_pushButtonWorkspace_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    ui->lineEditWorkspace->setText(dirPath);
}

void Options::on_pushButtonCompiler_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Sprout compiler"));
    ui->lineEditCompiler->setText(filePath);
}

void Options::on_buttonBox_accepted() {
    writeSettings();
}

void Options::readSettings() {
    settings.beginGroup("Path");
    ui->lineEditWorkspace->setText(settings.value("workspace").toString());
    ui->lineEditCompiler->setText(settings.value("sproutCompiler").toString());
    settings.endGroup();

    ui->checkBoxSession->setChecked(settings.value("MainWindow/restoreSession").toBool());
}

void Options::writeSettings() {
    settings.beginGroup("Path");
    settings.setValue("workspace", ui->lineEditWorkspace->text());
    settings.setValue("sproutCompiler", ui->lineEditCompiler->text());
    settings.endGroup();

    settings.setValue("MainWindow/restoreSession", ui->checkBoxSession->isChecked());
}
