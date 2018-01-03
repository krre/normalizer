#include "Options.h"
#include "ui_Options.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtCore>
#include <QtWidgets>

namespace IrbisCave {

Options::Options(QWidget* parent) :
        QDialog(parent),
        ui(new Ui::Options) {
    ui->setupUi(this);
    adjustSize();
    resize(600, height());
    readSettings();
}

Options::~Options() {
    delete ui;
}

void Options::on_pushButtonCore_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        ui->lineEditCore->setText(filePath);
    }
}

void Options::on_pushButtonStandard_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), QString(), "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        ui->lineEditStandard->setText(filePath);
    }
}

void Options::on_pushButtonWorkspace_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (!dirPath.isEmpty()) {
        ui->lineEditWorkspace->setText(dirPath);
    }
}

void Options::on_buttonBox_accepted() {
    writeSettings();
}

void Options::readSettings() {
    ui->lineEditCore->setText(Settings::instance()->value("IrbisLibrary/core").toString());
    ui->lineEditStandard->setText(Settings::instance()->value("IrbisLibrary/standard").toString());
    ui->lineEditWorkspace->setText(Settings::instance()->readWorkspace());
    ui->checkBoxSession->setChecked(Settings::instance()->readRestoreSession());
}

void Options::writeSettings() {
    Settings::instance()->setValue("IrbisLibrary/core", ui->lineEditCore->text());
    Settings::instance()->setValue("IrbisLibrary/standard", ui->lineEditStandard->text());
    Settings::instance()->setValue("Path/workspace", ui->lineEditWorkspace->text());
    Settings::instance()->setValue("MainWindow/restoreSession", ui->checkBoxSession->isChecked());
}

} // IrbisCave
