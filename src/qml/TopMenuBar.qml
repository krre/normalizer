import QtQuick 2.5
import QtQuick.Controls 1.4
import "../js/utils.js" as Utils

MenuBar {
    property alias recentFilesModel: recentFilesModel

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("New...")
            shortcut: "Ctrl+N"
            onTriggered: {
                var tab = tabView.addTab(qsTr("Untitled"))
                tab.setSource("qrc:/qml/AstArea.qml")
                tabView.currentIndex = tabView.count - 1
            }
        }

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
            onTriggered: {
                var fileDialog = Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogOpen.qml")
                fileDialog.accepted.connect(function() {
                    Utils.openFile(UTILS.urlToPath(fileDialog.fileUrl))
                })
            }
        }

        Menu {
            id: recentFilesMenu
            title: qsTr("Recent Files")
            enabled: recentFilesModel.count > 0

            Instantiator {
                model: recentFilesModel

                MenuItem {
                    text: model.filePath
                    onTriggered: Utils.openFile(text)
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
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Save")
            shortcut: "Ctrl+S"
            enabled: tabView.count > 0
            onTriggered: Utils.saveFile(currentTab.filePath)
        }

        MenuItem {
            text: qsTr("Save As...")
            shortcut: "Ctrl+Alt+S"
            enabled: tabView.count > 0
            onTriggered: Utils.saveAsFile()
        }

        MenuItem {
            text: qsTr("Save All")
            shortcut: "Ctrl+Shift+S"
            enabled: tabView.count > 0
            onTriggered: Utils.saveAllFiles()
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
            onTriggered: mainRoot.prepareAndClose()
        }
    }

    Menu {
        title: qsTr("Run")

        MenuItem {
            text: qsTr("Run")
            shortcut: "F9"
            enabled: currentTab && currentTab.filePath
            onTriggered: interpretator.run(currentTab.filePath)
        }
    }

    Menu {
        title: qsTr("Tools")

        MenuItem {
            text: qsTr("Options...")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/Options.qml")
        }
    }

    Menu {
        title: qsTr("Window")

        MenuItem {
            text: qsTr("Code Editor")
            shortcut: "Alt+1"
            onTriggered: currentTab.forceActiveFocus()
            enabled: tabView.count > 0
        }

        MenuItem {
            text: qsTr("Console")
            shortcut: "Alt+2"
            onTriggered: mainRoot.consoleArea.forceActiveFocus()
            enabled: tabView.count > 0
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr("About Greenery...")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/About.qml")
        }
    }
}
