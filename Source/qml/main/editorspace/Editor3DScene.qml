import QtQuick 2.8 as QQ2
import QtQuick.Scene3D 2.0
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Scene3D {
    aspects: ["input", "logic"]

    Entity {

        Camera {
            id: camera
            projectionType: CameraLens.PerspectiveProjection
            fieldOfView: 45
            nearPlane : 0.1
            farPlane : 1000.0
            position: Qt.vector3d( 0.0, 0.0, 40.0 )
            upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
            viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
        }

        OrbitCameraController { camera: camera }

        components: [
            RenderSettings {
                activeFrameGraph: ForwardRenderer {
                    camera: camera
                    clearColor: "transparent"
                }
            },
            InputSettings { }
        ]

        PhongMaterial {
            id: material
        }

        SphereMesh {
            id: sphereMesh
            radius: 3
        }

        Transform {
            id: sphereTransform
            property real userAngle: 0.0
            matrix: {
                var m = Qt.matrix4x4();
                m.rotate(userAngle, Qt.vector3d(0, 1, 0))
                m.translate(Qt.vector3d(0, 0, 0));
                return m;
            }
        }

        Entity {
            id: sphereEntity
            components: [ sphereMesh, material, sphereTransform ]
        }
    }
}
