import QtQuick 2.5
import OsgBridge 1.0 as Osg

UnitBase {
    objectName: "project"
    title: "Project"
    color: "pink"
    shape: Osg.Cylinder {
        radius: 0.1
        height: 0.2
    }
}
