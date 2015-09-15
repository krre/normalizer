import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import Greenery.Lib 1.0
import "../js/utils.js" as Utils
import "../js/command.js" as Command

ApplicationWindow {
    id: mainRoot
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    title: "Greenery"
    width: 800
    height: 600
    visible: true
    menuBar: TopMenuBar { id: topMenuBar }

    Component.onCompleted: {
        if (!Utils.loadGeometry()) {
            x = (Screen.width - width) / 2
            y = (Screen.height - height) / 2
        }
        Utils.loadRecentFiles()
        if (SETTINGS.getAutoLoadSession()) {
            Utils.loadSession()
        }
    }

    Component.onDestruction: {
        Utils.saveRecentFiles(topMenuBar.recentFilesModel)
        if (SETTINGS.getAutoLoadSession()) {
            Utils.saveSession()
        }
        Utils.saveGeometry()
    }

    TabView {
        id: tabView
        anchors.fill: parent
        frameVisible: false
    }
}
