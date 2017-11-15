#include "Options.h"
#include "ui_Options.h"
#include "Core/Defines.h"
#include <QtCore>
#include <QtWidgets>

Options::Options(QWidget* parent) :
        QDialog(parent),
        _ui(new Ui::Options),
        _settings(QCoreApplication::applicationDirPath() + "/" + APP_SETTINGS_NAME, QSettings::IniFormat) {
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
    _ui->lineEditWorkspace->setText(dirPath);
}

void Options::on_buttonBox_accepted() {
    writeSettings();
}

void Options::readSettings() {
    _settings.beginGroup("Path");
    _ui->lineEditWorkspace->setText(_settings.value("workspace", QDir::homePath() + "/" + WORKSPACE_DIRECTORY).toString());
    _settings.endGroup();

    _ui->checkBoxSession->setChecked(_settings.value("MainWindow/restoreSession", true).toBool());
}

void Options::writeSettings() {
    _settings.beginGroup("Path");
    _settings.setValue("workspace", _ui->lineEditWorkspace->text());
    _settings.endGroup();

    _settings.setValue("MainWindow/restoreSession", _ui->checkBoxSession->isChecked());
}
