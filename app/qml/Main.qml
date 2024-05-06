import QtCore
import QtQuick
import QtQuick.Controls
import "toolbar"

ApplicationWindow {
    property alias settings: settings
    id: appRoot
    width: 1200
    height: 800
    visible: true
    title: app.name

    Component.onCompleted: {
        appRoot.visibility = settings.window.visibility

        // Settings not exists - first start
        if (!(settings.window.width || settings.window.height)) {
            x = (Screen.desktopAvailableWidth - width) / 2
            y = (Screen.desktopAvailableHeight - height) / 2
        } else {
            settings.window.getGeometry(appRoot)
        }
    }

    onClosing: settings.window.setGeometry(appRoot)

    header: AppToolBar {}

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }

    AppSettings {
        id: settings
    }
}
