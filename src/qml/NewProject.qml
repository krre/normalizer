import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import "../js/utils.js" as Utils

Dialog {
    id: root
    title: qsTr("New Project")
    width: 500
    visible: true
    modality: Qt.ApplicationModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel

    onVisibilityChanged: {
        if (!visible) {
            root.destroy()
        }
    }

    onAccepted: {
        var path = directory.text + "/" + name.text + ".sprout"
        PROJECT.create(path)

        var tab = tabView.addTab(name.text)
        tab.setSource("qrc:/qml/WorkArea.qml", { filePath: path, projectName: name })
        tabView.currentIndex = tabView.count - 1
        Utils.addRecentFile(path)
        SETTINGS.setRecentDirectory(directory.text)
    }

    GridLayout {
        width: parent.width
        columns: 2

        Label {
            text: qsTr("Name:")
        }

        TextField {
            id: name
            Layout.fillWidth: true
            text: "project"
        }

        Label {
            text: qsTr("Module:")
        }

        TextField {
            id: module
            Layout.fillWidth: true
            text: "main"
        }

        Label {
            text: qsTr("Path:")
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: directory
                Layout.fillWidth: true
                text: SETTINGS.getRecentDirectory() ? SETTINGS.getRecentDirectory() : UTILS.homePath()
            }

            Button {
                text: qsTr("Browse...")
                onClicked: {
                    var fileDialog = Utils.createDynamicObject(mainRoot, "qrc:/qml/components/filedialog/FileDialogDirectory.qml", { folder: "file://" + directory.text })
                    fileDialog.accepted.connect(function() {
                        directory.text = UTILS.urlToPath(fileDialog.fileUrl)
                    })
                }
            }
        }
    }
}

