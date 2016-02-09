import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "main"
import "../js/utils.js" as Utils
import "../js/operators.js" as Operators

ApplicationWindow {
    id: mainRoot
    property alias tabView: tabView
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property alias sysPalette: sysPalette
    property var logger: new Utils.Logger()
    property var parentWindow: mainRoot
    title: Qt.application.name
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
        }
    }
}
