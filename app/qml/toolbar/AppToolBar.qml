import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "menu"

ToolBar {
    RowLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            action: Action {
                text: qsTr("Menu")
                onTriggered: optionsMenu.open()
            }

            AppMenu {
                id: optionsMenu
                x: parent.width - width
            }
        }
    }
}
