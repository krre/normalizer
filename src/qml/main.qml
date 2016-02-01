import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "main"
import "../js/utils.js" as Utils
import "../js/scene.js" as Scene

ApplicationWindow {
    id: mainRoot
    property var scene: new Scene.Scene()
    property var logger: new Utils.Logger()
    property alias sysPalette: sysPalette
    title: Qt.application.name
    width: Settings.value("MainWindow", "width", 800)
    height: Settings.value("MainWindow", "height", 600)
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = Settings.value("MainWindow", "x", (Screen.width - width) / 2)
        y = Settings.value("MainWindow", "y", (Screen.height - height) / 2)
    }

    onClosing: {
        Utils.saveGeometry("MainWindow")
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    TabView {
        id: tabView
        anchors.fill: parent
        frameVisible: false
    }
}
