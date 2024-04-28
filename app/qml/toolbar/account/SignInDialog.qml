import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    title: qsTr("Sign In")
    anchors.centerIn: parent
    standardButtons: Dialog.Ok | Dialog.Cancel
    closePolicy: Popup.CloseOnEscape

    Component.onDestruction: if (!visible) destroy()

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: email
            Layout.fillWidth: true
            placeholderText: qsTr("Email")
            focus: true
        }

        TextField {
            id: password
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
        }
    }
}
