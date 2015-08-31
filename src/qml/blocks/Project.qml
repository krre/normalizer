import QtQuick 2.5
import Qt3D.Renderer 2.0
import "../entities"

EntityBase {
    property alias arg: arg.text
    objectName: "project"
    mesh: SphereMesh {
        radius: 4
    }

    Text3D {
        id: arg
        x: -5
    }
}
