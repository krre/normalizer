import QtQuick 2.5
import Qt3D.Renderer 2.0
import "../entities"

EntityBase {
    property string arg

   Text3D {
        text: "print"
        x: 2
        y: 2
    }
}
