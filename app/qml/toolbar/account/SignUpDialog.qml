import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
 import QtQuick.Dialogs
import Normalizer

Dialog {
    title: qsTr("Sign Up")
    anchors.centerIn: parent
    standardButtons: Dialog.Ok | Dialog.Cancel
    modal: true
    closePolicy: Popup.CloseOnEscape

    Component.onDestruction: if (!visible) destroy()

    onAccepted: {
        account.create(login.text, email.text, fullName.text, password.text)
    }

    Account {
        id: account
        onErrorOccured: (status, message) => errorDialog.show(message)
    }

    MessageDialog {
        id: errorDialog
        buttons: MessageDialog.Ok
        parentWindow: appRoot

        function show(message) {
            text = message
            open()
        }
    }

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
