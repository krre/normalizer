import QtQuick 2.5
import Qt3D.Renderer 2.0
import "../entities"

EntityBase {
    objectName: "print"
    property alias arg: arg.text
    y: 10

    Text3D {
        id: arg
        text: "text"
        x: -4
    }
}
