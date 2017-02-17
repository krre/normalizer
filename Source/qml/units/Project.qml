import QtQuick 2.5
import QOsg 0.1 as QOsg

UnitBase {
    type: "project"
    title: qsTr("Project")
    color: "pink"
    shape: QOsg.Cylinder {
        radius: 0.02
        height: 0.04
    }
}
