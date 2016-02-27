import QtQuick 2.6
import QtQuick.Controls 1.5
import QtCanvas3D 1.1
import Greenery 1.0
import "../components"
import "../../js/utils.js" as Utils
import "../../js/operators.js" as Operators
import "../../js/dialog.js" as Dialog
import "../../js/gsg/gsg.js" as GSG
import "../../js/webgl/gl.js" as GL

Canvas3D {
    id: root
    property string title: Core.pathToFileName(path)
    property alias sproutDb: sproutDb
    property var scene
    property var camera
    property var gl
    property var panel
    property string path
    property bool isCurrent: root === currentTab
    property bool rendering: true
    renderOnDemand: true
//    renderOnDemand: !(isCurrent && rendering)

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
            scene = new GSG.Scene()
            // Load scene
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
