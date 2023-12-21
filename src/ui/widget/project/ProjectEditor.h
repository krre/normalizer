#pragma once
#include "core/CommonTypes.h"
#include "core/async/Task.h"
#include "ui/dialog/StandardDialog.h"

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
    Async::Task<void> createProject();
    Async::Task<void> updateProject();
    Async::Task<void> getProject();

    Controller::Project* m_project = nullptr;
    Id m_id = 0;
    QLineEdit* m_nameLineEdit = nullptr;
    QPlainTextEdit* m_descriptionTextEdit = nullptr;
    QComboBox* m_templateComboBox = nullptr;
};
