#pragma once
#include "StandardDialog.h"

class BrowseLineEdit;
class QCheckBox;

namespace Dialog {

class Options : public StandardDialog {
public:
    explicit Options(QWidget* parent = nullptr);

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
