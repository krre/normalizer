import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import Greenery 1.0
import "main"
import "../js/utils.js" as Utils

ApplicationWindow {
    id: mainRoot
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    title: Qt.application.name
    width: Settings.value("Main", "width", 800)
    height: Settings.value("Main", "height", 600)
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = Settings.value("Main", "x", (Screen.width - width) / 2)
        y = Settings.value("Main", "y", (Screen.height - height) / 2)

        Utils.loadRecentFiles()
        if (Settings.value("Common", "autoLoadSession", false)) {
            Utils.loadSession()
        }
    }

    onClosing: {
        Settings.setValue("Main", "x", x)
        Settings.setValue("Main", "y", y)
        Settings.setValue("Main", "width", width)
        Settings.setValue("Main", "height", height)

        Utils.saveRecentFiles()

        if (Settings.value("Common", "autoloadSession")) {
            Utils.saveSession()
        }

        // correct quit from app need close all tabs before
        for (var i = 0; i < tabView.count; i++) {
            tabView.removeTab(0)
        }
    }

    TabView {
        id: tabView
        anchors.fill: parent
        frameVisible: false
    }
}
