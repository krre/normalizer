import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.2
import "../components"
import "../../js/dialog.js" as Dialog
import "../../js/utils.js" as Utils

WindowDialog {
    id: root
    title: qsTr("New Project")
    width: 400
    height: 200

    onAccepted: {
        var dirPath = Settings.value("Path", "workspace") + "/" + name.text
        if (Core.isDirectoryExists(dirPath)) {
            Dialog.error(qsTr(String("Directory %1 is exists").arg(dirPath)))
            stayOnScreen = true
        } else {
            print(dirPath)
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
            text: qsTr("Workspace:")
        }

        Label {
            text: Settings.value("Path", "workspace")
        }
    }
}
