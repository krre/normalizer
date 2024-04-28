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
            text: qsTr("Menu")
            onClicked: appMenu.open()

            AppMenu {
                id: appMenu
                x: parent.width - width
            }
        }
    }
}
