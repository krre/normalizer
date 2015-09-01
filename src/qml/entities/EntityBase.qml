import QtQuick 2.5
import Qt3D 2.0
import Qt3D.Renderer 2.0

Entity {
    id: root
    property bool isCurrent: false
    property Material material: isCurrent ? phongMaterial : lambertMaterial
    property var mesh: CuboidMesh {
        xExtent: 5
        yExtent: 5
        zExtent: 5
    }

    property alias x: translateTransform.dx
    property alias y: translateTransform.dy
    property alias z: translateTransform.dz
    property alias scale: scaleTransform.scale

    components: [ mesh, material, transform ]

    Transform {
        id: transform
        Translate { id: translateTransform }
        Scale { id: scaleTransform }
    }

    Material {
        id: lambertMaterial
    }

    PhongMaterial {
        id: phongMaterial
    }
}
