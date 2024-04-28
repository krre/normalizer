import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 1200
    height: 800
    visible: true
    title: app.name

    Component.onCompleted: {
        root.visibility = windowSettings.visibility

        // Settings not exists - first start
        if (!(windowSettings.value("width") || windowSettings.value("height"))) {
            x = (Screen.desktopAvailableWidth - width) / 2
            y = (Screen.desktopAvailableHeight - height) / 2
        }
    }

    onClosing: windowSettings.visibility = root.visibility

    header: ToolBar {
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

    Settings {
        id: windowSettings
        category: "Window"
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
        property int visibility: Window.Windowed
    }
}
