import QtQuick 2.6
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog

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

        MenuItem {
            text: qsTr("Open...")
            shortcut: "Ctrl+O"
            onTriggered: {
                var dialog = Dialog.selectFile(mainRoot)
                dialog.accepted.connect(function() {
                    var path = Core.urlToPath(dialog.fileUrl)
                    var ext = Core.pathToExt(path)
                    if (ext === "impression") {
                        mainRoot.projectPath = Core.pathToDir(path)
                    }
                })
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
