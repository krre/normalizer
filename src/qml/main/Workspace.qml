import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQml.Models 2.2
import GreenSilage 1.0
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog

TreeView {
    id: root
    property string currentPath: fileSystemModel.path(selection.currentIndex)
    frameVisible: false
    model: fileSystemModel
    rootIndex: fileSystemModel.rootIndex
    selection: itemSelectionModel

    onDoubleClicked: Utils.openSprout(currentPath)

    Keys.onReturnPressed: Utils.openSprout(currentPath)

    function selectByPath(path) {
        var index = fileSystemModel.pathIndex(path)
        selection.setCurrentIndex(index, ItemSelectionModel.ClearAndSelect)
    }

    FileSystemModel {
        id: fileSystemModel
        rootDir: Settings.value("Path", "workspace", Core.homePath + "/greensilage")
    }

    ItemSelectionModel {
        id: itemSelectionModel
        model: fileSystemModel
    }

    MouseArea {
        z: -1
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onPressed:  {
            var index = indexAt(mouseX, mouseY)
            selection.setCurrentIndex(index, ItemSelectionModel.ClearAndSelect)
            if (currentPath) {
                fileMenu.popup()
            }
        }
    }

    Menu {
        id: fileMenu

        MenuItem {
            text: qsTr("Open")
            onTriggered: Utils.openSprout(currentPath)
        }

        MenuItem {
            text: qsTr("Remove...")
            onTriggered: {
                var dialog = Dialog.areYouSure(qsTr("Remove File"))
                dialog.yes.connect(function() {
                    var treeIndex = selection.currentIndex
                    if (fileSystemModel.removeFile(treeIndex)) {
                        var path = fileSystemModel.path(treeIndex)
                        var tabIndex = tabView.findTab(path)
                        if (tabIndex !== -1) {
                            tabView.removeTab(tabIndex)
                        }
                        mainMenu.recentFilesModel.removeByPath(path)
                    }
                })
            }
        }

        MenuItem {
            text: qsTr("Rename")
        }
    }

    TableViewColumn {
        title: qsTr("Workspace")
        role: "fileName"
        resizable: true
    }
}
