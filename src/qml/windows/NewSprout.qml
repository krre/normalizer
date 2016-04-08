import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.2
import Greenery 0.1
import "../components"
import "../../js/dialog.js" as Dialog
import "../../js/utils.js" as Utils

WindowDialog {
    id: root
    title: qsTr("New Sprout File")
    width: 400
    height: 100

    onAccepted: {
        var path = directory.text + "/" + name.text + ".sprout"
        if (Core.isFileExists(path)) {
            var dialog = Dialog.question(qsTr("File already exists. Overwrite?"))
            dialog.yes.connect(function() {
                createDb(path)
                root.close()
            })
            stayOnScreen = true
        } else {
            createDb(path)
        }
    }

    okButton.enabled: name.text

    function createDb(path) {
        var result = sproutDb.create(path)
        if (result) {
            Dialog.error(result)
        }
    }

    SproutDb {
        id: sproutDb
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
