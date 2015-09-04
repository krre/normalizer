import QtQuick 2.5
import "../../js/world.js" as World

NodeBase {
    name: "Module"
    onEdit: World.editModule(nodeId, name)
}
