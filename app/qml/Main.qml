import QtCore
import QtQuick
import QtQuick.Controls
import "toolbar"

ApplicationWindow {
    id: appRoot
    width: 1200
    height: 800
    visible: true
    title: app.name

    Component.onCompleted: {
        appRoot.visibility = windowSettings.visibility

        // Settings not exists - first start
        if (!(windowSettings.value("width") || windowSettings.value("height"))) {
            x = (Screen.desktopAvailableWidth - width) / 2
            y = (Screen.desktopAvailableHeight - height) / 2
        }
    }

    onClosing: windowSettings.visibility = appRoot.visibility

    header: AppToolBar {}

    Settings {
        id: windowSettings
        category: "Window"
        property alias x: appRoot.x
        property alias y: appRoot.y
        property alias width: appRoot.width
        property alias height: appRoot.height
        property int visibility: Window.Windowed
    }
}
