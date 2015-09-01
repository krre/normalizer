import QtQuick 2.5
import Qt3D.Renderer 2.0
import "../entities"

EntityBase {
    objectName: "floor"
    mesh: PlaneMesh {
        height: 50
        width: 50
        meshResolution: Qt.size(10, 10)
    }
}
