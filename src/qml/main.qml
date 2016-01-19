import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import Greenery 1.0
import "main"
import "../js/utils.js" as Utils

ApplicationWindow {
    id: mainRoot
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    title: "Greenery"
    width: SETTINGS.value("Main", "width", 800)
    height: SETTINGS.value("Main", "height", 600)
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = SETTINGS.value("Main", "x", (Screen.width - width) / 2)
        y = SETTINGS.value("Main", "y", (Screen.height - height) / 2)

        Utils.loadRecentFiles()
        if (SETTINGS.value("Common", "autoLoadSession", false)) {
            Utils.loadSession()
        }
    }

    onClosing: {
        SETTINGS.setValue("Main", "x", x)
        SETTINGS.setValue("Main", "y", y)
        SETTINGS.setValue("Main", "width", width)
        SETTINGS.setValue("Main", "height", height)

        Utils.saveRecentFiles()

        if (SETTINGS.value("Common", "autoloadSession")) {
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
