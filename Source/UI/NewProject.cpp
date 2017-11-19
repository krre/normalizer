#include "NewProject.h"
#include "ui_NewProject.h"

NewProject::NewProject(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::NewProject) {
    _ui->setupUi(this);
    adjustSize();
    resize(400, height());
}

NewProject::~NewProject() {
    delete _ui;
}
