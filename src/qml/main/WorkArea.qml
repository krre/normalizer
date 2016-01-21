import QtQuick 2.5
import QtQuick.Controls 1.4
import Greenery 1.0
import Osg 1.0 as Osg
import "../sheets"
import "../units"
import "../../js/command.js" as Command
import "../../js/utils.js" as Utils
import "../../js/world.js" as World

Item {
    id: root
    property alias commandSheet: commandSheet
    property alias output: output
    property alias process: process
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property string commandState: Command.Ready
    property var projectUnit
    property var currentUnit
    property var currentGeode
    property var sceneNode: viewer.sceneData
    property var sproutModel

    onCommandStateChanged: {
        if (commandState === Command.Ready) {
            forceActiveFocus()
        } else if (commandState === Command.Edit) {
            Utils.createDynamicObject(root, "qrc:/qml/dialogs/EditUnit.qml", { unit: currentUnit })
        } else if (commandState === Command.Info) {
            Utils.createDynamicObject(root, "qrc:/qml/dialogs/InfoUnit.qml", { unit: currentUnit })
        }
    }

    function home() {
        viewer.home()
    }

    function cancel() {
        commandState = Command.Ready
    }

    function save() {
        Utils.saveFile(filePath, projectUnit)
    }

    Component.onCompleted: {
        forceActiveFocus()
        World.createWorld(sceneGroup)
        currentGeode = projectUnit.geode.name
        viewer.home()
    }

    Keys.onPressed: Command.run(event)
    Keys.onEscapePressed: cancel()

    Process {
        id: process
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
        onPicked: currentGeode = name

        sceneData: Osg.Group {
            id: sceneGroup
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
