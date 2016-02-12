import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "../components"
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog

WindowDialog {
    property real indent: 10
    id: root
    title: qsTr("Options")
    width: 500
    height: 200

    onAccepted: {
        Settings.setValue("Path", "workspace", workspacePath.text)
        Settings.setValue("Interface", "restoreLastSession", lastSession.checked)
        Core.mkpath(workspacePath.text)
        workspace.rootDir = workspacePath.text
    }

    ColumnLayout {
        width: parent.width

        GroupBox {
            title: qsTr("Directory")
            Layout.preferredWidth: parent.width

            GridLayout {
                width: parent.width
                columns: 3

                Label {
                    text: qsTr("Workspace:")
                }

                TextField {
                    id: workspacePath
                    Layout.fillWidth: true
                    text: Settings.value("Path", "workspace")
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

        GroupBox {
            title: qsTr("Interface")
            Layout.preferredWidth: parent.width

            CheckBox {
                id: lastSession
                text: qsTr("Restore last session")
                checked: Utils.variantToBool(Settings.value("Interface", "restoreLastSession", false))
            }
        }
    }
}

