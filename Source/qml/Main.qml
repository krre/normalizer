import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Window 2.2
import "main"
import "../js/utils.js" as Utils

ApplicationWindow {
    id: mainRoot
    property string settingsGroup: "MainWindow"
    property var parentWindow: mainRoot
    title: Qt.application.name
    visible: true
    width: Settings.getValue(settingsGroup, "width", 800)
    height: Settings.getValue(settingsGroup, "height", 600)
    menuBar: MainMenu {}

    Component.onCompleted: {
        x = Settings.getValue(settingsGroup, "x", (Screen.width - width) / 2)
        y = Settings.getValue(settingsGroup, "y", (Screen.height - height) / 2)
        Utils.loadGeomerty(settingsGroup)
    }

    onClosing: {
        Utils.saveGeometry(settingsGroup)
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }
}
