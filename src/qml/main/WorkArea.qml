import QtQuick 2.6
import QtQuick.Controls 1.5
import QtCanvas3D 1.1
import "../../js/gl.js" as GL

Canvas3D {
    id: canvas3d
    property var gl
    anchors.fill: parent
    renderOnDemand: true

    onInitializeGL: GL.initializeGL(canvas3d)
    onResizeGL: GL.resizeGL(canvas3d)
    onPaintGL: GL.paintGL(canvas3d)
}
