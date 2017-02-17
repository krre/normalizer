import QtQuick 2.8
import QtQuick.Controls 1.5
import SproutE 0.1
import "../../components"
import "../../../js/utils.js" as Utils
import "../../../js/operators.js" as Operators
import "../../../js/dialog.js" as Dialog

Item {
    id: root
    property string title: Core.pathToFileName(path)
    property var panel
    property string path
    property bool isCurrent: root === editorTabView.currentTab
    property bool rendering: true
    property var program: ({})
    property SproutDb sproutDb: SproutDb {}

    Component.onCompleted: {
        reload()
    }

    onTitleChanged: updateTabTitle()

    Action {
        shortcut: " "
        enabled: root === editorTabView.currentTab && !panel
        onTriggered: Utils.createDynamicObject(root, "qrc:/qml/main/Finder.qml")
    }

    function reload() {
        sproutDb.close()
        var result = sproutDb.open(path)
        if (result) {
            Dialog.error(result)
        } else {
            // Load scene
        }
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
}
