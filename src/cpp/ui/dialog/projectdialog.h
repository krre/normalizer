#pragma once
#include <QDialog>
#include <QLineEdit>

class ProjectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ProjectDialog(QWidget *parent = 0);

public slots:
    void onAccepted();
    void onBrowseDirectory();

private:
    QLineEdit* directoryLineEdit;

};

