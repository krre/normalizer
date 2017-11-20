#pragma once
#include <QDialog>

namespace Ui {
    class NewFile;
}

class NewFile : public QDialog {
    Q_OBJECT

public:
    explicit NewFile(QWidget* parent = 0);
    ~NewFile();

private:
    Ui::NewFile* _ui;
};

