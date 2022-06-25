#pragma once
#include "StandardDialog.h"

class QLineEdit;
class QComboBox;

class NewProject : public StandardDialog {
    Q_OBJECT
public:
    explicit NewProject();
    QString path() const;

private slots:
    void onBrowseButtonClicked();
    void adjustAcceptedButton();

private:
    QLineEdit* nameLineEdit = nullptr;
    QLineEdit* directoryLineEdit = nullptr;
    QComboBox* templateComboBox = nullptr;
};
