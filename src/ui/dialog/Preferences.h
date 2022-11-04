#pragma once
#include "StandardDialog.h"

class BrowseLineEdit;
class QCheckBox;

namespace Dialog {

class Preferences : public StandardDialog {
public:
    explicit Preferences(QWidget* parent = nullptr);

private slots:
    void accept() override;

private:
    void readSettings();
    void writeSettings();

    BrowseLineEdit* workspaceBrowseLineEdit = nullptr;
    QCheckBox* openLastProjectCheckBox = nullptr;
    QCheckBox* sessionCheckBox = nullptr;
};

}
