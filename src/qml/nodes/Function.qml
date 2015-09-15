import QtQuick 2.5
import "../../js/world.js" as World

NodeBase {
    objectName: "function"
    name: "Function"
    onEdit: World.editFunction(nodeId, name)
}
