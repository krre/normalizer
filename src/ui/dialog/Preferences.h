#pragma once
#include "StandardDialog.h"
#include <QHostAddress>

class QLineEdit;

class Preferences : public StandardDialog {
public:
    struct Data {
        QHostAddress host;
        quint16 port;
    };

    Preferences(const Data& data, QWidget* parent = nullptr);
    Data data() const;

private:
    QLineEdit* m_hostLineEdit = nullptr;
    QLineEdit* m_portLineEdit = nullptr;
};
