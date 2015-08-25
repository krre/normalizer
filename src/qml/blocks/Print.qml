import QtQuick 2.5
import Qt3D.Renderer 2.0
import "../entities"

EntityBase {
    objectName: "print"
    property alias arg: arg.text

    Text3D {
        text: "print"
        x: 2
        y: 2
    }

    Text3D {
        id: arg
        text: "text"
        x: -2
        y: 0
    }
}
