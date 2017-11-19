#include "Options.h"
#include "ui_Options.h"
#include "Core/Defines.h"
#include "Core/Settings.h"
#include <QtCore>
#include <QtWidgets>

Options::Options(QWidget* parent) :
        QDialog(parent),
        _ui(new Ui::Options) {
    _ui->setupUi(this);
    adjustSize();
    resize(500, height());
    readSettings();
}

Options::~Options() {
    delete _ui;
}

void Options::on_pushButtonWorkspace_clicked() {
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (!dirPath.isEmpty()) {
        _ui->lineEditWorkspace->setText(dirPath);
    }
}

void Options::on_buttonBox_accepted() {
    writeSettings();
}

void Options::readSettings() {
    _ui->lineEditWorkspace->setText(Settings::instance()->readWorkspace());
    _ui->checkBoxSession->setChecked(Settings::instance()->readRestoreSession());
}

void Options::writeSettings() {
    Settings::instance()->setValue("Path/workspace", _ui->lineEditWorkspace->text());
    Settings::instance()->setValue("MainWindow/restoreSession", _ui->checkBoxSession->isChecked());
}
