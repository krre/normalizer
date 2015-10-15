import QtQuick 2.5
import QtQuick.Dialogs 1.2

Dialog {
    width: 400
    visible: true
    modality: Qt.ApplicationModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel
    onVisibleChanged: destroy()
}

