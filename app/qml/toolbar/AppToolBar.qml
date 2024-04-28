import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "menu"
import "account"

ToolBar {
    id: toolBar

    RowLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            text: qsTr("Account")
            onClicked: accountComp.createObject(appRoot).open()

            Component {
                id: accountComp
                Account {}
            }
        }

        ToolButton {
            text: qsTr("Menu")
            onClicked: appMenu.open()

            AppMenu {
                id: appMenu
                x: parent.width - width
                y: toolBar.height
            }
        }
    }
}
