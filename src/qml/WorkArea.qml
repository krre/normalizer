import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0
import QtQuick.Scene3D 2.0
import Greenery.Lib 1.0
import "sheets"
import "../js/command.js" as Command
import "../js/utils.js" as Utils
import "../js/world.js" as World

Item {
    id: root
    property alias sproutDb: sproutDb
    property alias commandSheet: commandSheet
    property alias output: output
    property alias cons: cons
    property bool isCurrentTab: mainRoot.currentTab === root
    property string filePath
    property string commandState: Command.Ready

    function reset() {
        camera.reset()
    }

    Component.onCompleted: {
        forceActiveFocus()
        sproutDb.open(filePath)
        World.createWorld()
    }

    Keys.onPressed: {
        Command.run(event)
    }

    SproutDb {
        id: sproutDb
    }

    Console {
        id: cons
        onMessage: output.textEdit.append(message)
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

    CommandSheet {
        id: commandSheet
        anchors.top: parent.top
        anchors.right: parent.right
    }

    Output {
        id: output
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
