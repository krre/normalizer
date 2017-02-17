import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "../components"
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog

WindowDialog {
    id: root
    title: qsTr("Select Workspace")
    width: 500
    height: 100

    onAccepted: {
        Settings.setValue("Path", "workspace", workspacePath.text)
        Core.mkpath(workspacePath.text)
        toolTabView.rootDir = workspacePath.text
    }

    onRejected: Qt.quit()

    GridLayout {
        width: parent.width
        columns: 3

        Label {
            text: qsTr("Workspace:")
        }

        TextField {
            id: workspacePath
            Layout.fillWidth: true
            text: Core.homePath + "/sprout"
            Component.onCompleted: forceActiveFocus()
        }

        BrowseButton {
            onClicked: {
                var dialog = Dialog.selectDirectory()
                dialog.accepted.connect(function() {
                    workspacePath.text = Core.urlToPath(dialog.fileUrl)
                })
            }
        }
    }
}
