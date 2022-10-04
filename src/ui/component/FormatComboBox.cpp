#include "FormatComboBox.h"

FormatComboBox::FormatComboBox() {
    addItem(tr("Binary"));
    addItem(tr("Binary / JSON"));
}

FileFormat FormatComboBox::format() const {
    return static_cast<FileFormat>(currentIndex());
}

void FormatComboBox::setFormat(FileFormat format) {
    setCurrentIndex(static_cast<int>(format));
}
