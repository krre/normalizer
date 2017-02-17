import QtQuick 2.5
import QOsg 0.1 as QOsg
import "../../js/world.js" as World

UnitBase {
    type: "function"
    title: qsTr("Function")
    color: "red"
    shape: QOsg.Cylinder {
        radius: 0.1
        height: 0.2
    }
}
