#include "FormatComboBox.h"

FormatComboBox::FormatComboBox() {
    addItem(tr("Binary"));
    addItem(tr("Binary And JSON"));
}

NormCommon::Project::Format FormatComboBox::format() const {
    return static_cast<NormCommon::Project::Format>(currentIndex());
}

void FormatComboBox::setFormat(NormCommon::Project::Format format) {
    setCurrentIndex(static_cast<int>(format));
}
