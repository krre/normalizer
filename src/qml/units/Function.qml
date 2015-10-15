import QtQuick 2.5
import OsgBridge 1.0 as Osg
import "../../js/world.js" as World

UnitBase {
    type: "function"
    title: qsTr("Function")
    onEdit: World.editFunction(unitId, name)
    color: "red"
    shape: Osg.Cylinder {
        radius: 0.1
        height: 0.2
    }
}
