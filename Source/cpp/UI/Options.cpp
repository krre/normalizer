#include "Options.h"
#include "ui_Options.h"
#include "../Defines.h"
#include <QtCore>

Options::Options(QWidget* parent) :
        QDialog(parent),
        ui(new Ui::Options),
        settings(QCoreApplication::applicationDirPath() + "/" + SETTINGS_NAME, QSettings::IniFormat) {
    ui->setupUi(this);
    adjustSize();
    resize(500, height());
}

Options::~Options() {
    delete ui;
}
