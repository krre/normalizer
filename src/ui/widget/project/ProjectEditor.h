#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/CommonTypes.h"

class QLineEdit;
class QPlainTextEdit;
class QComboBox;

class ProjectEditor : public StandardDialog {
public:
    explicit ProjectEditor(QWidget* parent = nullptr);
    explicit ProjectEditor(Id id, QWidget* parent = nullptr);

private:
    void setup();

    QLineEdit* m_nameLineEdit = nullptr;
    QPlainTextEdit* m_descriptionTextEdit = nullptr;
    QComboBox* m_templateComboBox = nullptr;
};
