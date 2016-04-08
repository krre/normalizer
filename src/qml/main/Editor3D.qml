import QtQuick 2.6
import QtQuick.Controls 1.5
import Greenery 1.0
import Osg 1.0 as Osg
import "../components"
import "../../js/utils.js" as Utils
import "../../js/operators.js" as Operators
import "../../js/dialog.js" as Dialog

Osg.Viewer {
    id: root
    property string title: Core.pathToFileName(path)
    property var panel
    property string path
    property bool isCurrent: root === currentTab
    property bool rendering: true
    property var program: ({})
    anchors.fill: parent
    allowThrow: true
    camera {
        clearColor: Qt.rgba(0.19, 0.12, 0.08, 1)
        fovy: 30
        aspectRatio: width / height
        zNear: 0.1
        zFar: 10000
    }

    sceneData: Osg.Geode {

        Osg.ShapeDrawable {
            color: "red"
            shape: Osg.Box {
                halfLengths: Qt.vector3d(0.5, 0.5, 0.5)
            }
        }
    }

    Component.onCompleted: {
        reload()
    }

    onTitleChanged: updateTabTitle()

    function reload() {
        sproutDb.close()
        var result = sproutDb.open(path)
        if (result) {
            Dialog.error(result)
        } else {
            // Load scene
        }
    }

    function action(index) {
        Operators.operators[index].action()
    }

    function updateTabTitle() {
        for (var i = 0; i < tabView.count; i++) {
            var tab = tabView.getTab(i)
            if (root === tab.item) {
                tab.title = title
                break
            }
        }
    }

    Action {
       shortcut: " "
       enabled: root == currentTab && !panel
       onTriggered: Utils.createDynamicObject(root, "qrc:/qml/main/Finder.qml")
    }

    SproutDb {
        id: sproutDb
    }
}
