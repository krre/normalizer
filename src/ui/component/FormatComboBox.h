#pragma once
#include "core/CommonTypes.h"
#include <QComboBox>

class FormatComboBox : public QComboBox {
public:
    FormatComboBox();

    FileFormats formats() const;
    void setFormats(FileFormats formats);

private:
    enum class Selection {
        Binary,
        BinaryAnnJson
    };
};
