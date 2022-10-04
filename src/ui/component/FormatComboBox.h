#pragma once
#include "core/CommonTypes.h"
#include <QComboBox>

class FormatComboBox : public QComboBox {
public:
    FormatComboBox();

    Format format() const;
    void setFormat(Format format);
};
