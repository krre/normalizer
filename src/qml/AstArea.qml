import QtQuick 2.5
import QtCanvas3D 1.0
import "../js/glcode.js" as GLCode
import "../js/command.js" as Command

Canvas3D {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property var astModel: ["Sprout"]
    visible: false

    Component.onCompleted: forceActiveFocus()

    onInitializeGL: {
        GLCode.initializeGL(root)
        root.visible = true
    }
    onPaintGL: GLCode.paintGL(root)

    Keys.onPressed: Command.run(event)

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.forceActiveFocus()
        }
    }
}

