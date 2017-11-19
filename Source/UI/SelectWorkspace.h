#pragma once
#include <QDialog>

namespace Ui {
    class SelectWorkspace;
}

class SelectWorkspace : public QDialog {
    Q_OBJECT

public:
    explicit SelectWorkspace(QWidget* parent = 0);
    ~SelectWorkspace();
    bool isRejected() const;

private slots:
    void on_pushButtonBrowse_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_lineEdit_textChanged(const QString& text);

private:
    Ui::SelectWorkspace* _ui;
    bool _isRejected = false;
};
