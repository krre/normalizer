import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtCanvas3D 1.1
import "main"
import "../js/utils.js" as Utils
import "../js/gl.js" as GL
import "../js/scene.js" as Scene

ApplicationWindow {
    id: mainRoot
    property var gl
    property var scene: new Scene.Scene()
    property var logger: new Utils.Logger()
    title: Qt.application.name
    width: 800
    height: 600
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        if (!Utils.loadGeomerty("MainWindow") && Screen.width && Screen.height) {
            x = (Screen.width - width) / 2
            y = (Screen.height - height) / 2
        }
    }

    onClosing: {
        Utils.saveGeometry("MainWindow")
    }

    Canvas3D {
        id: canvas3d
        anchors.fill: parent
        renderOnDemand: true

        onInitializeGL: GL.initializeGL(canvas3d)
        onResizeGL: GL.resizeGL(canvas3d)
        onPaintGL: GL.paintGL(canvas3d)
    }
}
