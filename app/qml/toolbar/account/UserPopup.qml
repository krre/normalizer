import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: root
    property alias content: content
    background: Rectangle {
        border.color: "gray"
    }

    ColumnLayout {
        id: content

        Label {
            id: username
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("User")
        }

        RowLayout {
            Button {
                text: qsTr("Edit")
                onClicked: {
                    root.close()
                }
            }

            Button {
                text: qsTr("Sign Out")
                onClicked: {
                    appRoot.settings.account.token = ""
                    root.close()
                }
            }
        }
    }
}
