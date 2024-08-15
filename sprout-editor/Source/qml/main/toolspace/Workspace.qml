import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQml.Models 2.2
import SproutE 0.1
import "../../../js/utils.js" as Utils
import "../../../js/dialog.js" as Dialog

TreeView {
    id: root
    property string currentPath: fileSystemModel.path(selection.currentIndex)
    property alias rootDir: fileSystemModel.rootDir
    property alias fileSystemModel: fileSystemModel
    frameVisible: false
    headerVisible: false
    sortIndicatorVisible: true
    model: fileSystemModel
    rootIndex: fileSystemModel.rootIndex
    selection: itemSelectionModel

    onSortIndicatorOrderChanged: fileSystemModel.sortFiles(sortIndicatorOrder)

    onDoubleClicked: Utils.openSprout(currentPath)

    Keys.onReturnPressed: Utils.openSprout(currentPath)

    function selectByPath(path) {
        var index = fileSystemModel.pathIndex(path)
        selection.setCurrentIndex(index, ItemSelectionModel.ClearAndSelect)
    }

    FileSystemModel {
        id: fileSystemModel
        rootDir: Settings.getValue("Path", "workspace", Core.homePath)
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
                    var path = fileSystemModel.path(treeIndex)
                    var tabIndex = editorTabView.findTab(path)
                    if (tabIndex >= 0) {
                        Dialog.error(qsTr("Need close tab with project before deleting"))
                    } else {
                        fileSystemModel.removeFile(treeIndex)
                        mainMenu.recentFilesModel.removeByPath(path)
                    }
                })
            }
        }

        MenuItem {
            text: qsTr("Rename...")
            onTriggered: Utils.createDynamicObject(root, "qrc:/qml/windows/Rename.qml", { path: currentPath })
        }
    }

    TableViewColumn {
        role: "fileName"
        resizable: true
    }
}
