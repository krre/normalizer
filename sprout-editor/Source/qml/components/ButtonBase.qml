import QtQuick 2.8
import QtQuick.Controls 1.5

Button {
    objectName: "ButtonBase"
    activeFocusOnPress: true
    isDefault: activeFocus

    Shortcut {
        sequence: "Return"
        enabled: isDefault
        onActivated: clicked()
    }

    Shortcut {
        sequence: "Enter"
        enabled: isDefault
        onActivated: clicked()
    }
}
