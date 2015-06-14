import QtQuick 2.5
import QtQuick.Controls 1.4
import "../js/utils.js" as Utils

MenuBar {
    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("New...")
            shortcut: "Ctrl+N"
            onTriggered: {
                tabView.addTab(qsTr("Untitled"))
            }
        }

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogOpen.qml")
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Save")
            shortcut: "Ctrl+S"
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Save As...")
            shortcut: "Ctrl+Alt+S"
            enabled: tabView.count > 0
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogSave.qml")
        }

        MenuItem {
            text: qsTr("Save All")
            shortcut: "Ctrl+Shift+S"
            enabled: tabView.count > 0
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Close")
            shortcut: "Ctrl+W"
            onTriggered: tabView.removeTab(tabView.currentIndex)
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Close All")
            shortcut: "Ctrl+Shift+W"
            onTriggered: {
                while (tabView.count > 0) {
                    tabView.removeTab(0)
                }
            }
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Close Other")
            enabled: tabView.count > 1
            onTriggered: {
                var i = 0
                while (tabView.count > 1) {
                    if (i !== tabView.currentIndex) {
                        tabView.removeTab(i)
                    } else {
                        i++
                    }
                }
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Exit")
            shortcut: "Ctrl+Q"
            onTriggered: Qt.quit()
        }
    }
}
