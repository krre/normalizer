import QtQuick 2.5
import Qt3D.Renderer 2.0
import "../entities"

EntityBase {
    objectName: "print"
    property alias arg: text3d.text
    y: 10

    Text3D {
        id: text3d
        text: "text"
        x: -4
    }
}
