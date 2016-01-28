import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtCanvas3D 1.1
import "main"
import "../js/gl.js" as GL

ApplicationWindow {
    id: mainRoot
    title: Qt.application.name
    width: 800
    height: 600
    visible: true
    menuBar: MainMenu { id: mainMenu }

    Component.onCompleted: {
        x = (Screen.width - width) / 2
        y = (Screen.height - height) / 2
    }

    Canvas3D {
        id: canvas3d
        anchors.fill: parent

        onInitializeGL: GL.initializeGL(canvas3d)
        onResizeGL: GL.resizeGL(canvas3d)
        onPaintGL: GL.paintGL(canvas3d)
    }
}
