import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    id: root
    property Material material: Material {}
    property var mesh: CuboidMesh {
        xExtent: 5
        yExtent: 5
        zExtent: 5
    }

    property alias x: translate.dx
    property alias y: translate.dy
    property alias z: translate.dz
    property alias scale: scaleTransform.scale

    components: [ mesh, material, transform ]

    Transform {
        id: transform
        Translate { id: translate }
        Scale { id: scaleTransform }
    }
}
