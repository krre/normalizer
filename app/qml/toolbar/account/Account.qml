import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
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
            Button {
                text: qsTr("Sign In")
            }

            Button {
                text: qsTr("Sign Up")
            }
        }
    }
}
