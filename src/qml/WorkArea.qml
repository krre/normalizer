import QtQuick 2.5
import Greenery 1.0
import OsgBridge 1.0 as Osg
import "sheets"
import "nodes"
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

    Component.onDestruction: {
        sproutDb.close()
    }

    onCommandStateChanged: {
        if (commandState === Command.Ready) {
            forceActiveFocus()
        }
    }

    function reset() {
        camera.reset()
    }

    function cancel() {
        commandState = Command.Ready
    }

    function createWorld() {
        sproutDb.open(filePath)
        World.createWorld()
    }

    Component.onCompleted: {
        forceActiveFocus()
//        createWorld()
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

    Osg.Viewer {
        anchors.fill: parent
        sceneData: Osg.Geode {
            Osg.Text {
                text: "Hello World!"
            }

//            Osg.ShapeDrawable {
//                shape: Osg.Box {
//                    halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
//                }
//            }

//            Osg.ShapeDrawable {
//                shape: Osg.Sphere {
//                    radius: 0.7
//                }
//            }
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
