import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    title: qsTr("Sign Up")
    anchors.centerIn: parent
    standardButtons: Dialog.Ok | Dialog.Cancel
    closePolicy: Popup.CloseOnEscape

    Component.onDestruction: if (!visible) destroy()

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: login
            Layout.fillWidth: true
            placeholderText: qsTr("Login")
            focus: true
        }

        TextField {
            id: fullName
            Layout.fillWidth: true
            placeholderText: qsTr("Full name")
        }

        TextField {
            id: email
            Layout.fillWidth: true
            placeholderText: qsTr("Email")
        }

        TextField {
            id: password
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
        }

        TextField {
            id: confirmPassword
            Layout.fillWidth: true
            placeholderText: qsTr("Confirm password")
        }
    }
}
