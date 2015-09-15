import QtQuick 2.5
import Qt3D.Renderer 2.0
import "../entities"

EntityBase {
    property alias arg: text3d.text
    objectName: "module"
    y: 10
    mesh: CylinderMesh {
        radius: 3
        length: 6
    }

    Text3D {
        id: text3d
        x: -4
    }
}
