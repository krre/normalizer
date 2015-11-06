import QtQuick 2.5
import QtQuick.Dialogs 1.2

Dialog {
    property bool isDestroyOnHide: true
    width: 400
    visible: true
    modality: Qt.ApplicationModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel
    onVisibleChanged: if (!visible && isDestroyOnHide) destroy()
}

