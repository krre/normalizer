.import "../js/utils.js" as Utils

function createWorld() {
    var map = sproutDb.readRecord("Defs")
    Utils.createDynamicObject(origin, "qrc:/qml/blocks/Project.qml", { arg: map.project })
}
