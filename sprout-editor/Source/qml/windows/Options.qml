import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "../components"
import "../../js/utils.js" as Utils
import "../../js/dialog.js" as Dialog

WindowDialog {
    id: root
    title: qsTr("Options")
    width: 500
    height: 200

    onAccepted: {
        Settings.setValue("Path", "workspace", workspacePath.text)
        Settings.setValue("Path", "compiler", compilerPath.text)
        Settings.setValue("Interface", "restoreLastSession", lastSession.checked)
        Core.mkpath(workspacePath.text)
        toolTabView.workspace.rootDir = workspacePath.text
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
                    text: Settings.getValue("Path", "workspace", "")
                    Component.onCompleted: forceActiveFocus()
                }

                BrowseButton {
                    onClicked: {
                        var dialog = Dialog.selectDirectory({ folder: "file://" + workspacePath.text })
                        dialog.accepted.connect(function() {
                            workspacePath.text = Core.urlToPath(dialog.fileUrl)
                        })
                    }
                }

                Label {
                    text: qsTr("Sprout Compiler:")
                }

                TextField {
                    id: compilerPath
                    Layout.fillWidth: true
                    text: Settings.getValue("Path", "compiler", "")
                    Component.onCompleted: forceActiveFocus()
                }

                BrowseButton {
                    onClicked: {
                        var dialog = Dialog.selectFile({ folder: "file://" + Core.pathToDir(compilerPath.text) })
                        dialog.accepted.connect(function() {
                            compilerPath.text = Core.urlToPath(dialog.fileUrl)
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
                checked: Settings.getValue("Interface", "restoreLastSession", false)
            }
        }
    }
}

