import QtQuick 2.5
import Greenery 0.1
import osg 2.0 as OSG
import osgGA 2.0 as OSGGA
import osgViewer 2.0 as OSGViewer
import "sheets"
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

    OSGViewer.View {
        id: view
        anchors.fill: parent
        cameraManipulator: OSGGA.TrackballManipulator { wheelZoomFactor: -0.1 }
        camera.clearColor: Qt.rgba(0.05, 0.05, 0.17, 1)
        sceneData: OSG.Group {

            OSG.Geode {

                OSG.ShapeDrawable {
                    color: "red"
                    shape: OSG.Cylinder {
                        center: Qt.vector3d(0, 0, 0)
                        radius: 0.2
                        height: 0.4
                    }
                }
            }
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
