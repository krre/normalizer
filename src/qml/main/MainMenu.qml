import QtQuick 2.6
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils

MenuBar {

    Menu {
        title: qsTr("File")

        Menu {
            title: qsTr("New")

            MenuItem {
                text: qsTr("Project...")
                onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/NewProject.qml")
            }

            MenuItem {
                text: qsTr("File")
                shortcut: "Ctrl+N"
                enabled: mainRoot.projectPath
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Exit")
            shortcut: "Ctrl+Q"
            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("Tools")

        MenuItem {
            text: qsTr("Options...")
            onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/Options.qml")
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
