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
    property alias editorTabView: editorTabView
    property Editor3D currentTab: editorTabView.count > 0 ? editorTabView.getTab(editorTabView.currentIndex).item : null
    property alias sysPalette: sysPalette
    property alias toolTabView: toolTabView
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

    onCurrentTabChanged: {
        if (currentTab) {
            currentTab.forceActiveFocus()
            toolTabView.workspace.selectByPath(currentTab.path)
        } else {
            toolTabView.workspace.selection.clearCurrentIndex()
        }
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
            visible: Utils.variantToBool(Settings.getValue("Gui", "showToolspace", true))

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
        }
    }
}
