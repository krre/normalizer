import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    property Material material: Material {}
    property var mesh: CuboidMesh {}

    property int x: 0
    property int y: 0
    property int z: 0

    components: [ mesh, material, transform ]

    Transform {
        id: transform
        Translate {
            translation: Qt.vector3d(x, y, z)
        }
    }
}
