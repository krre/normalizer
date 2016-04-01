import QtQuick 2.6
import QtQuick.Controls 1.5
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import QtQuick.Scene3D 2.0
import Greenery 1.0
import "../components"
import "../../js/utils.js" as Utils
import "../../js/operators.js" as Operators
import "../../js/dialog.js" as Dialog
import "../../js/gsg/gsg.js" as GSG
import "../../js/webgl/gl.js" as GL

Scene3D {
    id: root
    property string title: Core.pathToFileName(path)
    property var scene
    property var panel
    property string path
    property bool isCurrent: root === currentTab
    property bool rendering: true
    property SproutDb sproutDb: SproutDb {}
    property Action spaceAction: Action {
        shortcut: " "
        enabled: root == currentTab && !panel
        onTriggered: Utils.createDynamicObject(root, "qrc:/qml/main/Finder.qml")
    }
    aspects: "input"

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
            scene = new GSG.Scene()
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

    Entity {
        id: sceneRoot

        Camera {
            id: camera
            projectionType: CameraLens.PerspectiveProjection
            fieldOfView: 45
            aspectRatio: root.width / root.height
            nearPlane : 0.1
            farPlane : 1000.0
            position: Qt.vector3d( 0.0, 0.0, -40.0 )
            upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
            viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
        }

        Configuration  {
            controlledCamera: camera
        }

        FrameGraph {
            id: frameGraph
            activeFrameGraph: Viewport {
                id: viewport
                rect: Qt.rect(0.0, 0.0, 1.0, 1.0)
                clearColor: Qt.rgba(0.19, 0.12, 0.08, 1)

                CameraSelector {
                    id : cameraSelector
                    camera: camera

                    ClearBuffer {
                        buffers : ClearBuffer.ColorDepthBuffer
                    }
                }
            }
        }

        components: [ frameGraph ]

        Material {
            id: material
        }

        SphereMesh {
            id: sphereMesh
            radius: 3
        }

        CuboidMesh {
            id: cubeMesh
            xExtent: 5
            yExtent: 5
            zExtent: 5
        }

        Transform {
            id: cubeTransform
            translation: Qt.vector3d(10, 0.5, 0)
        }

        Transform {
            id: sphereTransform
            translation: Qt.vector3d(0, 0, 0)
        }

        Entity {
            components: [ sphereMesh, material, sphereTransform ]
        }

        Entity {
            components: [ cubeMesh, material, cubeTransform ]
        }
    }
}
