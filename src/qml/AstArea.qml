import QtQuick 2.5
import QtCanvas3D 1.0
import "../js/glcode.js" as GLCode

Canvas3D {
    id: root
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property var astModel
    visible: false

    onInitializeGL: {
        GLCode.initializeGL(root)
        root.visible = true
    }
    onPaintGL: GLCode.paintGL(root)
}

