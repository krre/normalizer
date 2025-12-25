#pragma once
#include "StandardDialog.h"
#include "core/async/Task.h"

class Network;

class QLineEdit;

class NewWorkspace : public StandardDialog {
    Q_OBJECT
public:
    NewWorkspace(Network* network);

    QString name() const;

public slots:
    void accept() override;

private slots:
    void setOkButtonState();

private:
    Async::Task<void> createWorkspace();

    Network* m_network = nullptr;
    QLineEdit* m_nameLineEdit = nullptr;
};
