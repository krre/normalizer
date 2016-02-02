import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQml.Models 2.2
import Impression 1.0
import "main"
import "../js/utils.js" as Utils
import "../js/scene.js" as Scene

ApplicationWindow {
    id: mainRoot
    property var scene: new Scene.Scene()
    property var logger: new Utils.Logger()
    property alias sysPalette: sysPalette
    property string projectPath
    title: Qt.application.name
    width: Settings.value("MainWindow", "width", 800)
    height: Settings.value("MainWindow", "height", 600)
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = Settings.value("MainWindow", "x", (Screen.width - width) / 2)
        y = Settings.value("MainWindow", "y", (Screen.height - height) / 2)
        Utils.loadRecentPaths("RecentFiles", mainMenu.recentFilesModel)
        Utils.loadRecentPaths("RecentProjects", mainMenu.recentProjectsModel)
        Utils.loadSession()
    }

    onClosing: {
        Utils.saveGeometry("MainWindow")
        Utils.saveRecentPaths("RecentFiles", mainMenu.recentFilesModel)
        Utils.saveRecentPaths("RecentProjects", mainMenu.recentProjectsModel)
        Utils.saveSession()
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    ProjectFileSystemModel {
        id: projectFileSystemModel
        rootDir: Core.pathToDir(projectPath)
    }

    SplitView {
        anchors.fill: parent
        visible: projectPath

        TreeView {
            id: treeView
            property string currentPath: projectFileSystemModel.path(treeView.selection.currentIndex)
            Layout.minimumWidth: 50
            width: 200
            height: parent.height
            model: projectFileSystemModel
            rootIndex: projectFileSystemModel.rootIndex
            selection: itemSelectionModel

            onDoubleClicked: Utils.openFile(projectFileSystemModel.path(index))

            ItemSelectionModel {
                id: itemSelectionModel
                model: projectFileSystemModel
            }

            MouseArea {
                z: -1
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onPressed:  {
                    var index = treeView.indexAt(mouseX, mouseY)
                    treeView.selection.setCurrentIndex(index, ItemSelectionModel.ClearAndSelect)
                    if (treeView.currentPath) {
                        fileMenu.popup()
                    }
                }
            }

            Menu {
                id: fileMenu

                MenuItem {
                    text: qsTr("Open File")
                    onTriggered: Utils.openFile(treeView.currentPath)
                }

                MenuItem {
                    text: qsTr("Remove File")
                    onTriggered: {
                        if (Core.pathToExt(treeView.currentPath) !== "impression") {
                            projectFileSystemModel.removeFile(treeView.selection.currentIndex)
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

        TabView {
            id: tabView
            Layout.fillWidth: true
            Layout.fillHeight: true
            frameVisible: false
        }
    }
}
