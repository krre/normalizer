import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Normalizer
import "../../dialog"

Dialog {
    id: root
    title: qsTr("Sign In")
    anchors.centerIn: parent
    modal: true
    closePolicy: Popup.CloseOnEscape

    onVisibleChanged: if (!visible) destroy()

    Account {
        id: account

        onLogined: (token) => {
            print(token)
            root.accept()
        }

        onErrorOccured: (status, message) => errorDialog.show(message)
    }

    ErrorDialog {
        id: errorDialog
    }

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

        DialogButtonBox {
            standardButtons: Dialog.Ok | Dialog.Cancel
            onAccepted: account.login(email.text, password.text)
            onRejected: root.reject()
        }
    }
}
