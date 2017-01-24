import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "main"
import "windows"
import "../js/utils.js" as Utils
import "../js/operators.js" as Operators

ApplicationWindow {
    id: mainRoot
    property alias tabView: tabView
    property Editor3D currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property alias sysPalette: sysPalette
    property alias workspace: workspace
    property var logger: new Utils.Logger()
    property var parentWindow: mainRoot
    title: Qt.application.name
    width: Settings.getValue("MainWindow", "width", 800)
    height: Settings.getValue("MainWindow", "height", 600)
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = Settings.getValue("MainWindow", "x", (Screen.width - width) / 2)
        y = Settings.getValue("MainWindow", "y", (Screen.height - height) / 2)
        Utils.loadSettings()
        Operators.add()
    }

    onCurrentTabChanged: {
        if (currentTab) {
            currentTab.forceActiveFocus()
            workspace.selectByPath(currentTab.path)
        } else {
            workspace.selection.clearCurrentIndex()
        }
    }

    onClosing: {
        Utils.saveSettings()
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    SelectWorkspace {
        visible: !Settings.getValue("Path", "workspace")
    }

    SplitView {
        anchors.fill: parent

        Workspace {
            id: workspace
            Layout.minimumWidth: 50
            width: Settings.getValue("Gui", "workspaceWidth", 200)
            visible: Utils.variantToBool(Settings.getValue("Gui", "showWorkspace", true))
        }

        TabView {
            id: tabView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            frameVisible: false

            function nextTab() {
                if (currentIndex + 1 < count) {
                    currentIndex++
                } else {
                    currentIndex = 0
                }
            }

            function previousTab() {
                if (currentIndex - 1 < 0) {
                    currentIndex = count - 1
                } else {
                    currentIndex--
                }
            }

            function findTab(path) {
                for (var i = 0; i < count; i++) {
                    if (getTab(i).item.path === path) {
                        return i
                    }
                }

                return -1
            }

            function forEachTab(callback) {
                for (var i = 0; i < count; i++) {
                    callback(getTab(i).item)
                }
            }
        }
    }
}
