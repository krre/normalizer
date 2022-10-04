#pragma once
#include "core/CommonTypes.h"
#include <QComboBox>

class FormatComboBox : public QComboBox {
public:
    FormatComboBox();

    FileFormat format() const;
    void setFormat(FileFormat format);
};
