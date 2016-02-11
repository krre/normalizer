import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.2
import "../components"
import "../../js/dialog.js" as Dialog
import "../../js/utils.js" as Utils

WindowDialog {
    id: root
    title: qsTr("New Sprout File")
    width: 400
    height: 100

    onAccepted: {
        var filePath = directory.text + "/" + name.text + ".sprout"
        if (Core.isFileExists(filePath)) {
            var dialog = Dialog.question(qsTr("File already exists. Overwrite?"))
            dialog.yes.connect(function() {
                Core.saveFile(filePath, "")
                Utils.openSprout(filePath)
                root.close()
            })
            stayOnScreen = true
        } else {
            Core.saveFile(filePath, "{}")
            Utils.openSprout(filePath)
        }
    }

    okButton.enabled: name.text

    GridLayout {
        width: parent.width
        columns: 2

        Label {
            text: qsTr("Name:")
        }

        TextField {
            id: name
            Layout.fillWidth: true
            Component.onCompleted: forceActiveFocus()
        }

        Label {
            text: qsTr("Directory:")
        }

        Label {
            id: directory
            text: Settings.value("Path", "workspace")
        }
    }
}
