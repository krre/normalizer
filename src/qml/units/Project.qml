import QtQuick 2.5
import Osg 1.0 as Osg

UnitBase {
    type: "project"
    title: qsTr("Project")
    color: "pink"
    shape: Osg.Cylinder {
        radius: 0.02
        height: 0.04
    }
}
