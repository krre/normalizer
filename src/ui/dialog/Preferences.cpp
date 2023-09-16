#include "Preferences.h"

Preferences::Preferences(QWidget* parent) : StandardDialog(parent) {
    setWindowTitle(tr("Preferences"));
    resizeToWidth(400);
}
