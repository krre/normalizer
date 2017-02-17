import QtQuick 2.8
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils

MenuBar {
    property alias recentFilesModel: recentFilesModel

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
        }

        Menu {
            id: recentFilesMenu
            title: qsTr("Recent Files")
            enabled: recentFilesModel.count > 0

            //@disable-check M300
            Instantiator {
                model: recentFilesModel

                MenuItem {
                    text: model.path
                }

                onObjectAdded: recentFilesMenu.insertItem(index, object)
                onObjectRemoved: recentFilesMenu.removeItem(object)
            }

            MenuSeparator {
                visible: recentFilesModel.count > 0
            }

            MenuItem {
                text: qsTr("Clear Menu")
                onTriggered: recentFilesModel.clear()
            }

            ListModel {
                id: recentFilesModel

                function removeByPath(path) {
                    for (var i = 0; i < count; i++) {
                        if (get(i).path === path) {
                            remove(i, 1)
                            break
                        }
                    }
                }
            }
        }

        MenuItem {
            text: qsTr("Reload")
            shortcut: "F5"
        }

        MenuItem {
            text: qsTr("Close")
            shortcut: "Ctrl+W"
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Exit")
            shortcut: "Ctrl+Q"
            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr("About %1...".arg(Qt.application.name))
        }
    }
}
