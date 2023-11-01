#pragma once
#include "StandardDialog.h"
#include <QHostAddress>

class QLineEdit;

class PreferencesDialog : public StandardDialog {
    friend class TestPreferences;
public:
    struct Data {
        QHostAddress host;
        quint16 port;
    };

    PreferencesDialog(const Data& data, QWidget* parent = nullptr);
    Data data() const;

private:
    QLineEdit* m_hostLineEdit = nullptr;
    QLineEdit* m_portLineEdit = nullptr;
};
