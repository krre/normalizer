import QtQuick 2.5
import "../../js/world.js" as World

NodeBase {
    objectName: "argument"
    name: "Argument"
    onEdit: World.editArgument(nodeId, name)
}
