import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQml.Models 2.2
import Impression 1.0
import "../../js/utils.js" as Utils

TreeView {
    id: root
    property string currentPath: projectFileSystemModel.path(selection.currentIndex)
    width: 200
    height: parent.height
    model: projectFileSystemModel
    rootIndex: projectFileSystemModel.rootIndex
    selection: itemSelectionModel

    onDoubleClicked: Utils.openFile(projectFileSystemModel.path(index))

    ProjectFileSystemModel {
        id: projectFileSystemModel
        rootDir: Core.pathToDir(projectPath)
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
            text: qsTr("Open File")
            onTriggered: Utils.openFile(root.currentPath)
        }

        MenuItem {
            text: qsTr("Remove File")
            onTriggered: {
                if (Core.pathToExt(root.currentPath) !== "impression") {
                    projectFileSystemModel.removeFile(root.selection.currentIndex)
                }
            }
        }

        MenuItem {
            text: qsTr("Rename File")
        }
    }

    TableViewColumn {
        title: qsTr("Project")
        role: "fileName"
        resizable: true
    }
}
