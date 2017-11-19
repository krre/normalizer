#pragma once
#include <QDialog>

namespace Ui {
    class NewProject;
}

class NewProject : public QDialog {
    Q_OBJECT

public:
    explicit NewProject(QWidget* parent = 0);
    ~NewProject();

private:
    Ui::NewProject* _ui;
};
