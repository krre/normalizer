import QtCore
import QtQuick
import QtQuick.Controls
import "toolbar"

ApplicationWindow {
    id: root
    width: 1200
    height: 800
    visible: true
    title: app.name

    Component.onCompleted: {
        root.visibility = windowSettings.visibility

        // Settings not exists - first start
        if (!(windowSettings.value("width") || windowSettings.value("height"))) {
            x = (Screen.desktopAvailableWidth - width) / 2
            y = (Screen.desktopAvailableHeight - height) / 2
        }
    }

    onClosing: windowSettings.visibility = root.visibility

    header: AppToolBar {}

    Settings {
        id: windowSettings
        category: "Window"
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
        property int visibility: Window.Windowed
    }
}
