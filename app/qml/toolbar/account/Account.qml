import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: root
    x: appRoot.width - content.width - 40
    y: toolBar.height
    background: Rectangle {
        border.color: "gray"
    }

    onVisibleChanged: if (!visible) destroy()

    ColumnLayout {
        id: content

        Label {
            id: username
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Guest")
        }

        RowLayout {
            Component {
                id: signInDialogComp
                SignInDialog {}
            }

            Component {
                id: signUpDialogComp
                SignUpDialog {}
            }

            Button {
                text: qsTr("Sign In")
                onClicked: {
                    signInDialogComp.createObject(appRoot).open()
                    root.close()
                }
            }

            Button {
                text: qsTr("Sign Up")
                onClicked: {
                    signUpDialogComp.createObject(appRoot).open()
                    root.close()
                }
            }
        }
    }
}
