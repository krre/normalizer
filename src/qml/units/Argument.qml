import QtQuick 2.5
import Osg 1.0 as Osg
import "../../js/world.js" as World

UnitBase {
    type: "argument"
    title: qsTr("Argument")
    color: "blue"
    shape: Osg.Sphere {
        radius: 0.1
    }
}
