import QtQuick 2.5
import OsgBridge 1.0 as Osg
import "../../js/world.js" as World

UnitBase {
    objectName: "argument"
    title: "Argument"
    onEdit: World.editArgument(unitId, name)
    color: "blue"
    shape: Osg.Sphere {
        radius: 0.1
    }
}
