import QtQuick 2.8
import QOsg 0.1 as QOsg
import "../../js/world.js" as World

UnitBase {
    type: "argument"
    title: qsTr("Argument")
    color: "blue"
    shape: QOsg.Sphere {
        radius: 0.1
    }
}
