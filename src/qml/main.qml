import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import Greenery.Lib 1.0
import "sheets"
import "../js/utils.js" as Utils
import "../js/command.js" as Command

ApplicationWindow {
    id: mainRoot
    property string version: "0.1.0"
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property alias output: output
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
        Utils.loadSession()
    }

    Component.onDestruction: {
        Utils.saveRecentFiles(topMenuBar.recentFilesModel)
        Utils.saveSession()
        Utils.saveGeometry()
    }

    Console {
        id: cons
        onMessage: output.textEdit.append(message)
    }

    TabView {
        id: tabView
        anchors.fill: parent
    }

    Output {
        id: output
        width: parent.width
        anchors.bottom: parent.bottom
    }

    CommandSheet {
        id: commandSheet
        anchors.top: parent.top
        anchors.bottom: output.top
        anchors.topMargin: 30
        anchors.right: parent.right
    }
}
