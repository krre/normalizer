import QtQuick 2.5
import Greenery.Lib 1.0
import "../js/command.js" as Command

Item {
    id: root
    property alias sproutDb: sproutDb
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property bool isNew: false

    function reset() {
    }

    Component.onCompleted: {
        forceActiveFocus()
        if (isNew) {
            sproutDb.create(filePath)
        } else {
            sproutDb.open(filePath)
        }
    }

    Keys.onPressed: Command.run(event)

    SproutDb {
        id: sproutDb
    }
}
