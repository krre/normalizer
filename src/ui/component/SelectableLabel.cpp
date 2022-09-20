#include "SelectableLabel.h"

SelectableLabel::SelectableLabel(const QString& text, QWidget* parent) : QLabel(text, parent) {
    setup();
}

SelectableLabel::SelectableLabel(QWidget* parent) : QLabel(parent) {
    setup();
}

void SelectableLabel::setup() {
    setTextInteractionFlags(textInteractionFlags() | Qt::TextSelectableByMouse);
}
