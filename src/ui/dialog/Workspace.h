#pragma once
#include "StandardDialog.h"

class QLineEdit;

class Workspace : public StandardDialog {
public:
    explicit Workspace(QWidget* parent = nullptr);

protected slots:
    void accept() override;

private slots:
    void onBrowseButtonClicked();
    void adjustAcceptedButton(const QString& text);

private:
    QLineEdit* lineEdit = nullptr;
};
