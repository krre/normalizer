import QtQuick 2.6
import QtQuick.Controls 1.5
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog

MenuBar {
    property alias recentFilesModel: recentFilesModel
    property alias recentProjectsModel: recentProjectsModel

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
                onTriggered: Utils.createDynamicObject(mainRoot, "qrc:/qml/main/NewFile.qml")
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
                    if (ext === "impr") {
                        Utils.openProject(path)
                    } else if (ext === "sprout") {
                        Utils.openFile(path)
                    } else {
                        print("Error: unknown path")
                    }
                })
            }
        }

        Menu {
            id: recentFilesMenu
            title: qsTr("Recent Files")
            enabled: recentFilesModel.count > 0

            Instantiator {
                model: recentFilesModel

                MenuItem {
                    text: model.path
                    onTriggered: Utils.openProject(text)
                }

                onObjectAdded: recentFilesMenu.insertItem(index, object)
                onObjectRemoved: recentFilesMenu.removeItem(object)
            }

            MenuSeparator {
                visible: recentFilesModel.count > 0
            }

            MenuItem {
                text: qsTr("Clear Menu")
                onTriggered: recentFilesModel.clear()
            }

            ListModel {
                id: recentFilesModel
            }
        }

        Menu {
            id: recentProjectsMenu
            title: qsTr("Recent Projects")
            enabled: recentProjectsModel.count > 0

            Instantiator {
                model: recentProjectsModel

                MenuItem {
                    text: model.path
                    onTriggered: Utils.openProject(text)
                }

                onObjectAdded: recentProjectsMenu.insertItem(index, object)
                onObjectRemoved: recentProjectsMenu.removeItem(object)
            }

            MenuSeparator {
                visible: recentProjectsModel.count > 0
            }

            MenuItem {
                text: qsTr("Clear Menu")
                onTriggered: recentProjectsModel.clear()
            }

            ListModel {
                id: recentProjectsModel
            }
        }

        MenuSeparator {}

        MenuItem {
            text: qsTr("Close Project")
            enabled: mainRoot.projectPath
            onTriggered: mainRoot.projectPath = ""
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
