import QtQuick 2.6
import QtQuick.Controls 1.5
import QtCanvas3D 1.1
import "../../js/gl.js" as GL

Canvas3D {
    id: root
    property var program: Object()
    property var gl
    property string path
    objectName: "3d"
    renderOnDemand: true

    onInitializeGL: GL.initializeGL(root)
    onResizeGL: GL.resizeGL(root)
    onPaintGL: GL.paintGL(root)

    Action {
        shortcut: " "
        enabled: root == currentTab
        onTriggered: finder.visible = true
    }

    Action {
        shortcut: "Esc"
        enabled: root == currentTab
        onTriggered: {
            if (finder.visible) {
                finder.visible = false
            }
        }
    }

    Finder {
        id: finder
        anchors.centerIn: parent
    }
}
