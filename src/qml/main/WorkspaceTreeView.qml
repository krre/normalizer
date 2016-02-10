import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQml.Models 2.2
import GreenSilage 1.0
import "../../js/utils.js" as Utils

TreeView {
    id: root
    property string currentPath: projectFileSystemModel.path(selection.currentIndex)
    frameVisible: false
    model: projectFileSystemModel
    rootIndex: projectFileSystemModel.rootIndex
    selection: itemSelectionModel

    onDoubleClicked: Utils.openSprout(projectFileSystemModel.path(index))

    ProjectFileSystemModel {
        id: projectFileSystemModel
        rootDir: Settings.value("Path", "workspace", Core.homePath + "/greensilage")
    }

    ItemSelectionModel {
        id: itemSelectionModel
        model: projectFileSystemModel
    }

    MouseArea {
        z: -1
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onPressed:  {
            var index = root.indexAt(mouseX, mouseY)
            root.selection.setCurrentIndex(index, ItemSelectionModel.ClearAndSelect)
            if (root.currentPath) {
                fileMenu.popup()
            }
        }
    }

    Menu {
        id: fileMenu

        MenuItem {
            text: qsTr("Open")
            onTriggered: Utils.openSprout(root.currentPath)
        }

        MenuItem {
            text: qsTr("Remove")
            onTriggered: {
                var treeIndex = root.selection.currentIndex
                if (projectFileSystemModel.removeFile(treeIndex)) {
                    var tabIndex = tabView.findTab(projectFileSystemModel.path(treeIndex))
                    if (tabIndex !== -1) {
                        tabView.removeTab(tabIndex)
                    }
                }
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
