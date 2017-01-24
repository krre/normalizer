import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import "main"
import "main/editorspace"
import "main/toolspace"
import "windows"
import "../js/utils.js" as Utils
import "../js/operators.js" as Operators

ApplicationWindow {
    id: mainRoot
    property alias toolTabView: toolTabView
    property alias editorTabView: editorTabView
    property alias sysPalette: sysPalette
    property var logger: new Utils.Logger()
    property var parentWindow: mainRoot
    title: Qt.application.name
    width: Settings.getValue("MainWindow", "width", 800)
    height: Settings.getValue("MainWindow", "height", 600)
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = Settings.getValue("MainWindow", "x", (Screen.width - width) / 2)
        y = Settings.getValue("MainWindow", "y", (Screen.height - height) / 2)
        Utils.loadSettings()
        Operators.add()
    }

    onClosing: {
        Utils.saveSettings()
    }

    SystemPalette {
        id: sysPalette
        colorGroup: SystemPalette.Active
    }

    SelectWorkspace {
        visible: !Settings.getValue("Path", "workspace")
    }

    SplitView {
        anchors.fill: parent

        ColumnLayout {
            id: toolspace
            Layout.minimumWidth: 50
            width: Settings.getValue("Gui", "toolspaceWidth", 200)
            visible: Settings.getValue("Gui", "showToolspace", true)

            ComboBox {
                Layout.preferredWidth: parent.width
                model: [ qsTr("Workspace") ]
            }

            ToolTabView {
                id: toolTabView
                Layout.preferredWidth: parent.width
                Layout.fillHeight: true
            }
        }

        EditorTabView {
            id: editorTabView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50

            onCurrentTabChanged: {
                if (editorTabView.currentTab) {
                    editorTabView.currentTab.forceActiveFocus()
                    toolTabView.workspace.selectByPath(editorTabView.currentTab.path)
                } else {
                    toolTabView.workspace.selection.clearCurrentIndex()
                }
            }
        }
    }
}
