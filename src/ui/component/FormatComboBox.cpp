#include "FormatComboBox.h"

FormatComboBox::FormatComboBox() {
    addItem(tr("Binary"));
    addItem(tr("Binary / JSON"));
}

FileFormats FormatComboBox::formats() const {
    Selection selection = static_cast<Selection>(currentIndex());
    return FileFormats(selection == Selection::Binary ? BinaryFormat : (BinaryFormat | JsonFormat));
}

void FormatComboBox::setFormats(FileFormats formats) {
    Selection selection = formats.testFlag(JsonFormat) ? Selection::BinaryAnnJson : Selection::Binary;
    setCurrentIndex(static_cast<int>(selection));
}
