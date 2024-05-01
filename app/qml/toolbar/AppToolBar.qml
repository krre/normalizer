import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "menu"
import "account"

ToolBar {
    id: toolBar

    AccountPopup {
        id: accountPopup
        x: appRoot.width - content.width - 20
        y: toolBar.height
    }

    RowLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
        }

        ToolButton {
            text: qsTr("Account")
            onClicked: accountPopup.open()
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
