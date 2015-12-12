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
    width: 800
    height: 600
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        if (!Utils.loadGeometry()) {
            x = (Screen.width - width) / 2
            y = (Screen.height - height) / 2
        }
        Utils.loadRecentFiles()
        if (SETTINGS.autoLoadSession()) {
            Utils.loadSession()
        }
    }

    onClosing: {
        Utils.saveRecentFiles(mainMenu.recentFilesModel)
        if (SETTINGS.autoLoadSession()) {
            Utils.saveSession()
        }
        Utils.saveGeometry()

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
