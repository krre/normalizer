import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import Greenery.Lib 1.0
import "../js/utils.js" as Utils

ApplicationWindow {
    id: mainRoot
    property string version: "0.1.0"
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    property alias consoleArea: consoleArea
    property alias status: statusBar.status
    title: "Greenery"
    width: 800
    height: 600
    visible: true
    menuBar: TopMenuBar { id: topMenuBar }
    statusBar: StatusBar {
        Label {
            id: statusBar
            property string status
            text: status ? status : qsTr("Ready")
        }
    }

    Component.onCompleted: {
        if (!Utils.loadGeometry()) {
            x = (Screen.width - width) / 2
            y = (Screen.height - height) / 2
        }
        Utils.loadRecentFiles()
        Utils.loadSession()
    }

    onClosing: {
        close.accepted = false
        prepareAndClose()
    }

    function prepareAndClose() {
        Utils.saveRecentFiles(topMenuBar.recentFilesModel)
        Utils.saveSession()
        Utils.saveGeometry()

        // clearing tab bar to prevent crash caused canvas3d in Qt 5.5 RC1
        while (tabView.count > 0) {
            tabView.removeTab(tabView.currentIndex)
        }

        Qt.quit()
    }

    Interpretator {
        id: interpretator
        onConsoleMessage: consoleArea.append(message)
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        TabView {
            id: tabView
            Layout.minimumHeight: 50
            Layout.fillHeight: true

        }

        TextArea {
            id: consoleArea
            Layout.minimumHeight: 50
            height: 50
            backgroundVisible: false
            readOnly: true
        }
    }
}


