#pragma once
#include <NormCommon/Project.h>
#include <QComboBox>

class FormatComboBox : public QComboBox {
public:
    FormatComboBox();

    NormCommon::Project::Format format() const;
    void setFormat(NormCommon::Project::Format format);
};

