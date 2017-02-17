import QtQuick 2.8
import QOsg 0.1 as QOsg

UnitBase {
    type: "instruction"
    title: qsTr("Instruction")
    color: "yellow"
    shape: QOsg.Sphere {
        radius: 0.1
    }
}
