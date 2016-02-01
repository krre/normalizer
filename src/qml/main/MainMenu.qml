import QtQuick 2.6
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils

MenuBar {

    Menu {
        title: qsTr("File")

        MenuItem {
            text: qsTr("Exit")
            shortcut: "Ctrl+Q"
            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("Help")

        MenuItem {
            text: qsTr(String("About %1...").arg(Qt.application.name))
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/About.qml")
        }
    }
}
