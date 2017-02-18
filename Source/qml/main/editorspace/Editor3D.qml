import QtQuick 2.8
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.2
import SproutE 0.1
import ".."
import "../../components"
import "../../../js/utils.js" as Utils
import "../../../js/operators.js" as Operators
import "../../../js/dialog.js" as Dialog
import "../../../js/style.js" as Style

Rectangle {
    id: root
    readonly property string title: Core.pathToFileName(path)
    property alias process: process
    property alias output: output
    property alias sproutDb: sproutDb
    property var panel
    property string path
    property bool isCurrent: root === editorTabView.currentTab
    property bool rendering: true
    property var program: ({})
    color: Style.editor3DBackground

    Component.onCompleted: {
        load()
        output.appendMessage(qsTr("Project %1 is loaded").arg(title))
    }

    Component.onDestruction: {
        sproutDb.close()
        Settings.setValue("Gui", "showOutput", output.visible)
        Settings.setValue("Gui", "outputHeight", output.height)
    }

    onTitleChanged: updateTabTitle()

    Action {
        shortcut: " "
        enabled: root === editorTabView.currentTab && !panel
        onTriggered: Utils.createDynamicObject(root, "qrc:/qml/main/Finder.qml")
    }

    Process {
        id: process
        onMessage: output.appendMessage(message)
    }

    SproutDb {
        id: sproutDb
    }

    function reload() {
        sproutDb.close()
        load()
        output.appendMessage(qsTr("Project %1 is reloaded").arg(title))
    }

    function load() {
        var result = sproutDb.open(path)
        if (result) {
            Dialog.error(result)
        } else {
            // Load scene
        }
    }

    function build() {
        var compilerPath = Settings.getValue("Path", "compiler")
        if (!Core.isFileExists(compilerPath)) {
            Dialog.error("Path to compiler is wrong\n" + compilerPath)
        } else {
           process.run(compilerPath, path)
        }
    }

    function home() {
        // TODO
        print("Set camera to home position")
    }

    function action(index) {
        Operators.operators[index].action()
    }

    function updateTabTitle() {
        for (var i = 0; i < editorTabView.count; i++) {
            var tab = editorTabView.getTab(i)
            if (root === tab.item) {
                tab.title = title
                break
            }
        }
    }

    SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        Item {
            id: editor
            width: parent.width
            Layout.fillHeight: true
            Layout.minimumHeight: 50
        }

        Output {
            id: output
            width: parent.width
            height: Settings.getValue("Gui", "outputHeight", 120)
            Layout.minimumHeight: 50
            visible: Settings.getValue("Gui", "showOutput", true)
        }
    }
}
