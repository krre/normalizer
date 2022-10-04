#include "FormatComboBox.h"

FormatComboBox::FormatComboBox() {
    addItem(tr("Binary"));
    addItem(tr("Binary / JSON"));
}

Format FormatComboBox::format() const {
    return static_cast<Format>(currentIndex());
}

void FormatComboBox::setFormat(Format format) {
    setCurrentIndex(static_cast<int>(format));
}
