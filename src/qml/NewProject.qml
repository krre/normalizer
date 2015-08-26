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
        var path = directory.text + "/" + file.text + ".sprout"
        PROJECT.create(path, name.text)

        var tab = tabView.addTab(name.text)
        tab.setSource("qrc:/qml/WorkArea.qml", { filePath: path })
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
            text: qsTr("File:")
        }

        TextField {
            id: file
            Layout.fillWidth: true
            text: "project-1.0"
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

        Label {
            id: template
            text: qsTr("Template:")
        }

        ComboBox {
            Layout.fillWidth: true
            model: ["Empty", "Hello World"]
        }
    }
}

