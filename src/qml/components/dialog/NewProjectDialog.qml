import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import "../../../js/utils.js" as Utils
import "../../../js/dialog.js" as Dialog

DialogBase {
    id: root
    title: qsTr("New Project")
    width: 500

    onAccepted: {
        var path = directory.text + "/" + name.text + ".sprout"
        for(var i = 0; i < tabView.count; i++) {
            var tab = tabView.getTab(i).item
            if (tabView.getTab(i).item.filePath === path) {
                tabView.currentIndex = i
                Dialog.infoMessage(qsTr("File is open. Close file first"))
                return
            }
        }
        if (UTILS.isFileExists(path)) {
            isDestroyOnHide = false
            var dialog = Dialog.questionMessage(qsTr("File already exists. Overwrite?"))
            dialog.yes.connect(function() {
                UTILS.removeFile(path)
                Utils.newFile(directory.text, name.text)
                root.destroy()
            })

            dialog.no.connect(function() { root.open() })
        } else {
            Utils.newFile(directory.text, name.text)
        }
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
            text: qsTr("Directory:")
        }

        RowLayout {
            Layout.fillWidth: true

            TextField {
                id: directory
                Layout.fillWidth: true
                text: SETTINGS.value("Path", "recentDirectory", UTILS.homePath)
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
