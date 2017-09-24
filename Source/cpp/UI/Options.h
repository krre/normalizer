#pragma once
#include <QDialog>
#include <QSettings>

namespace Ui {
    class Options;
}

class Options : public QDialog {
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private slots:
    void on_pushButtonWorkspace_clicked();
    void on_pushButtonCompiler_clicked();
    void on_buttonBox_accepted();

private:
    Ui::Options *ui;
    QSettings settings;

    void readSettings();
    void writeSettings();
};
