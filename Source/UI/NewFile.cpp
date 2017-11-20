#include "NewFile.h"
#include "ui_NewFile.h"

NewFile::NewFile(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::NewFile) {
    _ui->setupUi(this);
    adjustSize();
    resize(500, height());
}

NewFile::~NewFile() {
    delete _ui;
}
