import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    RowLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            action: Action {
                id: optionsMenuAction
                text: qsTr("Menu")
                onTriggered: optionsMenu.open()
            }

            Menu {
                id: optionsMenu
                x: parent.width - width
                transformOrigin: Menu.TopRight

                Component {
                    id: aboutDialogComp
                    AboutDialog {}
                }

                Action {
                    text: qsTr("About %1").arg(app.name)
                    onTriggered: aboutDialogComp.createObject(root)
                }
            }
        }
    }
}
