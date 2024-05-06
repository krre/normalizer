import QtCore
import QtQuick

Item {
    id: root
    property alias window: window
    property alias account: account

    Settings {
        id: window
        category: "Window"
        property int x
        property int y
        property int width
        property int height
        property int visibility: Window.Windowed

        function setGeometry(appWindow) {
            x = appWindow.x
            y = appWindow.y
            width = appWindow.width
            height = appWindow.height
            visibility = appWindow.visibility
        }

        function getGeometry(appWindow) {
            appWindow.x = x
            appWindow.y = y
            appWindow.width = width
            appWindow.height = height
        }
    }

    Settings {
        id: account
        category: "Account"
        property string token
    }
}
