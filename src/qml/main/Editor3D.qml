import QtQuick 2.6
import QtQuick.Controls 1.5
import QtCanvas3D 1.1
import "../../js/gl.js" as GL

Canvas3D {
    id: root
    property var gl
    property string path
    objectName: "3d"
    renderOnDemand: true
    visible: Qt.platform.os !== "linux"

    onInitializeGL: GL.initializeGL(root)
    onResizeGL: GL.resizeGL(root)
    onPaintGL: GL.paintGL(root)

    Action {
        shortcut: " "
        onTriggered: print("space")
        enabled: root == currentTab
    }
}
