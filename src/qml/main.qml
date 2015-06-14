import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

ApplicationWindow {
    property string version: "0.1.0"
    property var currentTab: tabView.count > 0 ? tabView.getTab(tabView.currentIndex).item : null
    id: mainRoot
    title: "Greenery"
    width: 800
    height: 600
    visible: true
    menuBar: TopMenuBar {}

    Component.onCompleted: {
        x = (Screen.width - width) / 2
        y = (Screen.height - height) / 2
    }

    TabView {
        id: tabView
        anchors.fill: parent
    }
}


