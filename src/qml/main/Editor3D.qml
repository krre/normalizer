import QtQuick 2.6
import QtQuick.Controls 1.5
import QtCanvas3D 1.1
import Usilage 1.0
import "../components"
import "../../js/utils.js" as Utils
import "../../js/operators.js" as Operators
import "../../js/dialog.js" as Dialog
import "../../js/webgl/gl.js" as GL
import "../../js/webgl/scene.js" as Scene

Canvas3D {
    id: root
    property string title: Core.pathToFileName(path)
    property alias sproutDb: sproutDb
    property var scene: new Scene.Scene()
    property var program: Object()
    property var currentNode
    property var gl
    property var pos
    property var panel
    property string path
    property bool isCurrent: root === currentTab
    property bool rendering: true
    renderOnDemand: !(isCurrent && rendering)

    Component.onCompleted: {
        reload()
    }

    onInitializeGL: GL.initializeGL(root)
    onResizeGL: GL.resizeGL(root)
    onPaintGL: GL.paintGL(root)

    onTitleChanged: updateTabTitle()

    // For debug purpose
    onRenderingChanged: print("Render %1: %2".arg(path).arg(rendering ? "On" : "Off"))

    function updateTabTitle() {
        for (var i = 0; i < tabView.count; i++) {
            var tab = tabView.getTab(i)
            if (root === tab.item) {
                tab.title = title
                break
            }
        }
    }

    function reload() {
        sproutDb.close()
        var result = sproutDb.open(path)
        if (result) {
            Dialog.error(result)
        } else {
            currentNode = program
            pos = { moduleId: 0 }
        }
    }

    function action(index) {
        Operators.operators[index].action()
    }

    SproutDb {
        id: sproutDb
    }

    Action {
        shortcut: " "
        enabled: root == currentTab && !panel
        onTriggered: Utils.createDynamicObject(root, "qrc:/qml/main/Finder.qml")
    }
}
