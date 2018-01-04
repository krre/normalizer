#pragma once
#include <QDialog>

namespace Ui {
    class NewProject;
}

namespace IrbisCave {

class NewProject : public QDialog {
    Q_OBJECT

public:
    explicit NewProject(QWidget* parent = 0);
    ~NewProject();
    QString getProjectPath() const;

private slots:
    void on_pushButtonBrowse_clicked();
    void on_buttonBox_accepted();
    void on_lineEditName_textChanged(const QString& text);
    void on_lineEditLocation_textChanged(const QString& text);

private:
    void changeOkButtonState();

    Ui::NewProject* ui;
    QString projectPath;
};

} // IrbisCave
