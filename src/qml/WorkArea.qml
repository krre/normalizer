import QtQuick 2.5
import "../js/command.js" as Command

Item {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath

    function reset() {
    }

    Component.onCompleted: {
        forceActiveFocus()
    }

    Keys.onPressed: Command.run(event)
}
