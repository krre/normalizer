import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "../components"
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
                    text: Settings.value("Path", "workspace", Core.homePath + "/impression")
                    Component.onCompleted: forceActiveFocus()
                }

                BrowseButton {
                    onClicked: {
                        var selectDirectoryDialog = Dialog.selectDirectory(root)
                        selectDirectoryDialog.accepted.connect(function() {
                            workspacePath.text = Core.urlToPath(selectDirectoryDialog.fileUrl)
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
                checked: Settings.value("Interface", "restoreLastSession", false)
            }
        }
    }
}

