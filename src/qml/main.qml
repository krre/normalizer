import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
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
    }

    onClosing: {
        Utils.saveGeometry("MainWindow")
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    ProjectFileSystemModel {
        id: projectFileSystemModel
        rootDir: projectPath
    }

    SplitView {
        anchors.fill: parent
        visible: projectPath

        TreeView {
            id: treeView
            Layout.minimumWidth: 50
            width: 200
            height: parent.height
            headerVisible: false
            model: projectFileSystemModel
            rootIndex: projectFileSystemModel.rootIndex

            TableViewColumn {
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
