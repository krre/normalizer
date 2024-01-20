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
class QLabel;

class ProjectEditor : public StandardDialog {
public:
    explicit ProjectEditor(Controller::Project* project, QWidget* parent = nullptr);
    explicit ProjectEditor(Controller::Project* project, Id id, QWidget* parent = nullptr);

public slots:
    void accept() override;

private:
    enum class State {
        Add,
        Edit
    };

    void createForm();

    Async::Task<void> createProject();
    Async::Task<void> updateProject();
    Async::Task<void> getProject();

    const QStringList m_templates = { tr("Binary"), tr("Library") };

    Controller::Project* m_project = nullptr;
    Id m_id = 0;
    const State m_state;

    QLineEdit* m_nameLineEdit = nullptr;
    QPlainTextEdit* m_descriptionTextEdit = nullptr;
    QComboBox* m_templateComboBox = nullptr;
    QLabel* m_templateLabel = nullptr;
};
