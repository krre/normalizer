import QtQuick 2.5
import QtQuick.Controls 1.4
import Greenery 1.0
import OsgBridge 1.0 as Osg
import "sheets"
import "units"
import "../js/command.js" as Command
import "../js/utils.js" as Utils
import "../js/world.js" as World

Item {
    id: root
    property alias sproutDb: sproutDb
    property alias commandSheet: commandSheet
    property alias output: output
    property alias cons: cons
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property string commandState: Command.Ready
    property var currentNode
    property var sceneNode: viewer.sceneData

    Component.onDestruction: {
        sproutDb.close()
    }

    onCommandStateChanged: {
        if (commandState === Command.Ready) {
            forceActiveFocus()
        }
    }

    function home() {
        viewer.home()
    }

    function cancel() {
        commandState = Command.Ready
    }

    Component.onCompleted: {
        forceActiveFocus()
        sproutDb.open(filePath)
        World.createWorld(sceneGroup)
        viewer.home()
    }

    Keys.onPressed: {
        Command.run(event)
    }

    Keys.onEscapePressed: cancel()

    SproutDb {
        id: sproutDb
    }

    Console {
        id: cons
        onMessage: output.textEdit.append(message)
    }

    UnitSet { id: unitSet }

    Osg.Viewer {
        id: viewer
        anchors.fill: parent
        camera {
            clearColor: "gray"
            fovy: 30
            aspectRatio: width / height
            zNear: 0.1
            zFar: 10000
        }
        onPicked: currentNode = name

        sceneData: Osg.Group {
            id: sceneGroup
        }
    }

    Column {

        TextField {
            id: textField
            text: "Hello"
        }
    }

    CommandSheet {
        id: commandSheet
        anchors.top: parent.top
        anchors.right: parent.right
    }

    Output {
        id: output
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
