import QtQuick 2.6
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog

MenuBar {
    property alias recentFilesModel: recentFilesModel

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("New...")
            shortcut: "Ctrl+N"
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/NewSprout.qml")
        }

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
            onTriggered: {
                var dialog = Dialog.selectFile()
                dialog.accepted.connect(function() {
                    var path = Core.urlToPath(dialog.fileUrl)
                    if (Core.pathToExt(path) === "sprout") {
                        Utils.openSprout(path)
                    } else {
                        print(qsTr("Error: unknown path"))
                    }
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
                    text: model.path
                    onTriggered: Utils.openSprout(text)
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

        MenuSeparator {}

        MenuItem {
            text: qsTr("Save")
            shortcut: "Ctrl+S"
            enabled: currentTab && currentTab.isDirty
            onTriggered:  currentTab.save()
        }

        MenuItem {
            text: qsTr("Save As...")
            shortcut: "Ctrl+Shift+S"
            enabled: currentTab
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogSave.qml")
        }

        MenuItem {
            text: qsTr("Reload")
            shortcut: "F5"
            enabled: currentTab
            onTriggered: currentTab.reload()
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Close")
            shortcut: "Ctrl+W"
            enabled: tabView.count > 0
            onTriggered: tabView.removeTab(tabView.currentIndex)
        }

        MenuItem {
            text: qsTr("Close All")
            shortcut: "Ctrl+Shift+W"
            enabled: tabView.count > 0
            onTriggered: {
                while (tabView.count > 0) {
                    tabView.removeTab(0)
                }
            }
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

    Menu {
        title: qsTr("Edit")

        MenuItem {
            text: qsTr("Undo")
            shortcut: "Ctrl+Z"
        }

        MenuItem {
            text: qsTr("Redo")
            shortcut: "Ctrl+Shift+Z"
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Cut")
            shortcut: "Ctrl+X"
        }

        MenuItem {
            text: qsTr("Copy")
            shortcut: "Ctrl+C"
        }

        MenuItem {
            text: qsTr("Paste")
            shortcut: "Ctrl+V"
        }
    }

    Menu {
        title: qsTr("Run")

        MenuItem {
            text: qsTr("Run Module")
            shortcut: "F9"
            onTriggered: print("run")
        }

        MenuItem {
            text: qsTr("Stop")
            shortcut: "Ctrl+Pause"
            onTriggered: print("stop")
        }
    }

    Menu {
        title: qsTr("Tools")

        MenuItem {
            text: qsTr("Options...")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/Options.qml")
        }
    }

    Menu {
        title: qsTr("Window")

        MenuItem {
           text: qsTr("Full Screen")
           shortcut: "F11"
           checkable: true
           onTriggered: checked ? mainRoot.showFullScreen() : mainRoot.showNormal()
        }

        MenuItem {
            text: qsTr("Show Workspace")
            shortcut: "Ctrl+1"
            checkable: true
            checked: workspace.visible
            onCheckedChanged: workspace.visible = checked
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Next Tab")
            shortcut: "Ctrl+Tab"
            enabled: tabView.count > 1
            onTriggered: tabView.nextTab()
        }

        MenuItem {
            text: qsTr("Previous Tab")
            shortcut: "Ctrl+Shift+Tab"
            enabled: tabView.count > 1
            onTriggered: tabView.previousTab()
        }
    }

    Menu {
        title: qsTr("Debug")
        visible: isDebug
        enabled: isDebug

        Menu {
            title: qsTr("Render")
            enabled: currentTab

            MenuItem {
                text: qsTr("Run Current")
                onTriggered: currentTab.renderOnDemand = false
            }

            MenuItem {
                text: qsTr("Run All")
                onTriggered: tabView.forEachTab(function(editor) { editor.renderOnDemand = false })
                shortcut: "Ctrl+F11"
            }

            MenuItem {
                text: qsTr("Stop Current")
                onTriggered: currentTab.renderOnDemand = true
            }

            MenuItem {
                text: qsTr("Stop All")
                onTriggered: tabView.forEachTab(function(editor) { editor.renderOnDemand = true })
                shortcut: "Ctrl+F12"
            }
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr("About %1...".arg(Qt.application.name))
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/About.qml")
        }
    }
}
