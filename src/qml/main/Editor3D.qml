import QtQuick 2.6
import QtQuick.Controls 1.5
import QtCanvas3D 1.1
import "../../js/webgl/gl.js" as GL
import "../../js/webgl/scene.js" as Scene

Canvas3D {
    id: root
    property string title: "{ " + Core.pathToFileName(path) + (isDirty ? "*" : "") + " }"
    property string type: "3d"
    property var scene: new Scene.Scene()
    property var program: Object()
    property var gl
    property string path
    property bool isDirty: false
    renderOnDemand: true

    Component.onCompleted: {
        reload()
    }

    onInitializeGL: GL.initializeGL(root)
    onResizeGL: GL.resizeGL(root)
    onPaintGL: GL.paintGL(root)

    onTitleChanged: updateTabTitle()

    function updateTabTitle() {
        for (var i = 0; i < tabView.count; i++) {
            var tab = tabView.getTab(i)
            if (root === tab.item) {
                tab.title = title
                break
            }
        }
    }

    function save() {
        Core.saveFile(path, JSON.stringify(program, null, 4))
        isDirty = false
    }

    function reload() {
        try {
            program = JSON.parse(Core.loadFile(path))
            isDirty = false
        } catch(e) {
            print(qsTr("Opening ") + path + ": " + e)
        }
    }

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
