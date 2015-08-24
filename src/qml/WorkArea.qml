import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0
import QtQuick.Scene3D 2.0
import Greenery.Lib 1.0
import "../js/command.js" as Command
import "../js/utils.js" as Utils

Item {
    id: root
    property alias sproutDb: sproutDb
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property bool isNew: false

    function reset() {
    }

    Component.onCompleted: {
        forceActiveFocus()
        if (isNew) {
            sproutDb.create(filePath)
        } else {
            sproutDb.open(filePath)
        }

        Utils.createDynamicObject(origin, "qrc:/qml/entities/Cube.qml", { x: 10 })
        Utils.createDynamicObject(origin, "qrc:/qml/entities/Sphere.qml", { x: -10 })
    }

    Keys.onPressed: {
        Command.run(event)
    }

    SproutDb {
        id: sproutDb
    }

    Scene3D {
        anchors.fill: parent
        aspects: "input"

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
                // disabled to prevent crash on close tab
//                controlledCamera: camera
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

            Entity {
                id: origin
            }
        }
    }
}
