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
    property string module
    property string projectName: UTILS.urlToFileName()

    function reset() {
        camera.reset()
    }

    Component.onCompleted: {
        forceActiveFocus()
        if (isNew) {
            sproutDb.create(filePath)
        } else {
            sproutDb.open(filePath)
        }

//        Utils.createDynamicObject(origin, "qrc:/qml/blocks/Print.qml", { arg: "hello world" })
        Utils.createDynamicObject(origin, "qrc:/qml/blocks/Project.qml", { arg: projectName })
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
                fieldOfView: 90
                aspectRatio: root.width / root.height
                nearPlane : 0.1
                farPlane : 1000.0

                Component.onCompleted: reset()

                function reset() {
                    upVector = Qt.vector3d( 0.0, 1.0, 0.0 )
                    position = Qt.vector3d( 0.0, 0.0, -40.0 )
                    viewCenter = Qt.vector3d( 0.0, 0.0, 0.0 )
                }
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
                    clearColor: Qt.rgba(0.05, 0.05, 0.17, 1)

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
