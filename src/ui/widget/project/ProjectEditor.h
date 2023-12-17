#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/CommonTypes.h"

namespace Controller {
    class Project;
}

class QLineEdit;
class QPlainTextEdit;
class QComboBox;

class ProjectEditor : public StandardDialog {
public:
    explicit ProjectEditor(Controller::Project* project, QWidget* parent = nullptr);
    explicit ProjectEditor(Controller::Project* project, Id id, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    Controller::Project* m_project = nullptr;
    Id m_id = 0;

    QLineEdit* m_nameLineEdit = nullptr;
    QPlainTextEdit* m_descriptionTextEdit = nullptr;
    QComboBox* m_templateComboBox = nullptr;
};
