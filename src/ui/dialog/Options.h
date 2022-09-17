#pragma once
#include "StandardDialog.h"

class BrowseLineEdit;
class QCheckBox;

class Options : public StandardDialog {
public:
    explicit Options(QWidget* parent = nullptr);

private slots:
    void accept() override;

private:
    void readSettings();
    void writeSettings();

    BrowseLineEdit* workspaceBrowseLineEdit = nullptr;
    QCheckBox* sessionCheckBox = nullptr;
};
