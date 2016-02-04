import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import Impression 1.0
import "main"
import "../js/utils.js" as Utils
import "../js/scene.js" as Scene
import "../js/operators.js" as Operators

ApplicationWindow {
    id: mainRoot
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property var scene: new Scene.Scene()
    property var logger: new Utils.Logger()
    property alias sysPalette: sysPalette
    property string projectPath
    property var projectSettings: Object()
    title: Qt.application.name + (projectPath ? String(" [%1]").arg(projectPath) : "")
    width: Settings.value("MainWindow", "width", 800)
    height: Settings.value("MainWindow", "height", 600)
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = Settings.value("MainWindow", "x", (Screen.width - width) / 2)
        y = Settings.value("MainWindow", "y", (Screen.height - height) / 2)
        Utils.loadSettings()
        Operators.add()
    }

    onCurrentTabChanged: {
        if (currentTab) {
            currentTab.forceActiveFocus()
        }
    }

    onClosing: {
        Utils.saveSettings()
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    SplitView {
        anchors.fill: parent
        visible: projectPath

        ProjectTreeView {
            id: projectTreeView
            Layout.minimumWidth: 50
            width: Settings.value("Gui", "projectTreeWidth", 200)
        }

        TabView {
            id: tabView
            Layout.fillWidth: true
            Layout.fillHeight: true
            frameVisible: false
        }
    }
}
