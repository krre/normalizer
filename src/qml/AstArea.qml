import QtQuick 2.5
import QtCanvas3D 1.0
import "../3rdparty"
import "../js/glcode.js" as GLCode
import "../js/command.js" as Command

Canvas3D {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property var astModel: []
    property var currentNode

    Component.onCompleted: {
        astModel.push({ lang: ["Sprout", "0.1.0"] })
        currentNode = astModel
        forceActiveFocus()
    }

    onInitializeGL: {
        GLCode.initializeGL(root, eventSource)
        root.visible = true
    }
    onPaintGL: GLCode.paintGL(root)

    Keys.onPressed: Command.run(event)

    ControlEventSource {
        id: eventSource
        anchors.fill: parent
        focus: true
        onMouseDown: root.forceActiveFocus()
    }
}

