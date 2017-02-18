import QtQuick 2.8
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
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/windows/NewSprout.qml")
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

            //@disable-check M300
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
            text: qsTr("Save As...")
            shortcut: "Ctrl+Shift+S"
            enabled: editorTabView.currentTab
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogSave.qml")
        }

        MenuItem {
            text: qsTr("Reload")
            shortcut: "F5"
            enabled: editorTabView.currentTab
            onTriggered: editorTabView.currentTab.reload()
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Close")
            shortcut: "Ctrl+W"
            enabled: editorTabView.count > 0
            onTriggered: editorTabView.removeTab(editorTabView.currentIndex)
        }

        MenuItem {
            text: qsTr("Close All")
            shortcut: "Ctrl+Shift+W"
            enabled: editorTabView.count > 0
            onTriggered: {
                while (editorTabView.count > 0) {
                    editorTabView.removeTab(0)
                }
            }
        }

        MenuItem {
            text: qsTr("Close Other")
            enabled: editorTabView.count > 1
            onTriggered: {
                var i = 0
                while (editorTabView.count > 1) {
                    if (i !== editorTabView.currentIndex) {
                        editorTabView.removeTab(i)
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
        title: qsTr("Build")
        visible: editorTabView.currentTab

        MenuItem {
            text: qsTr("Build Project") + " " + editorTabView.currentTab.title
            shortcut: "Ctrl+B"
            enabled: editorTabView.currentTab
            onTriggered: editorTabView.currentTab.build()
        }

        MenuItem {
            text: qsTr("Stop")
            shortcut: "Ctrl+Pause"
            onTriggered: print("stop")
        }
    }

    Menu {
        title: qsTr("Camera")
        visible: editorTabView.currentTab

        MenuItem {
            text: qsTr("Home")
            onTriggered: editorTabView.currentTab.home()
            shortcut: "F12"
        }
    }

    Menu {
        title: qsTr("Tools")

        MenuItem {
            text: qsTr("Options...")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/windows/Options.qml")
        }
    }

    Menu {
        title: qsTr("Window")
        visible: editorTabView.currentTab

        MenuItem {
           text: qsTr("Full Screen")
           shortcut: "F11"
           checkable: true
           onTriggered: checked ? mainRoot.showFullScreen() : mainRoot.showNormal()
        }

        MenuItem {
            text: qsTr("Clear Output")
            shortcut: "Shift+Del"
            onTriggered: editorTabView.currentTab.output.textEdit.text = ""
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Show Toolspace")
            shortcut: "Ctrl+1"
            checkable: true
            checked: toolspace.visible
            onCheckedChanged: toolspace.visible = checked
        }

        MenuItem {
            text: qsTr("Output")
            shortcut: "Ctrl+2"
            checkable: true
            checked: editorTabView.currentTab ? editorTabView.currentTab.output.visible : false
            onTriggered: editorTabView.currentTab.output.visible = !editorTabView.currentTab.output.visible
        }

//        MenuItem {
//            text: qsTr("Command Sheet")
//            checkable: true
//            checked: true
//            onTriggered: editorTabView.currentTab.commandSheet.visible = !editorTabView.currentTab.commandSheet.visible
//        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Next Tab")
            shortcut: "Ctrl+Tab"
            enabled: editorTabView.count > 1
            onTriggered: editorTabView.nextTab()
        }

        MenuItem {
            text: qsTr("Previous Tab")
            shortcut: "Ctrl+Shift+Tab"
            enabled: editorTabView.count > 1
            onTriggered: editorTabView.previousTab()
        }
    }

    Menu {
        title: qsTr("Debug")
        visible: debugMode
        enabled: debugMode

        Menu {
            title: qsTr("Render")
            enabled: editorTabView.currentTab

            MenuItem {
                text: qsTr("Enable")
                onTriggered: editorTabView.forEachTab(function(editor) { editor.rendering = true })
                shortcut: "Ctrl+F11"
            }

            MenuItem {
                text: qsTr("Disable")
                onTriggered: editorTabView.forEachTab(function(editor) { editor.rendering = false })
                shortcut: "Ctrl+F12"
            }
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr("About %1...".arg(Qt.application.name))
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/windows/About.qml")
        }
    }
}
