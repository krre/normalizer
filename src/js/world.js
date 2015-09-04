.import "../js/utils.js" as Utils

function createWorld() {
    addFloor()
//    currentNode = addProject(origin)
    currentNode = addProject(scene2d)
}

function lastId(table) {
    var module = sproutDb.readRecords(String("SELECT seq FROM sqlite_sequence WHERE name='%1'").arg(table))
    return module.length ? module[0].seq : 0
}

// ******************************** ADD *************************************

function addFloor() {
//    return Utils.createDynamicObject(origin, "qrc:/qml/blocks/Floor.qml")
}

function addProject(parent) {
    var record = sproutDb.readRecords("SELECT value FROM Defs WHERE name='project'")
//    return Utils.createDynamicObject(parent, "qrc:/qml/blocks/Project.qml", { arg: record[0].value })
    return Utils.createDynamicObject(parent, "qrc:/qml/nodes/Project.qml", { arg: record[0].value, x: 10, y: 10 })
}

function addModule(parent) {
    var id = parseInt(lastId("Modules")) + 1
    var name = "module" + id
    sproutDb.insertRecord(String("INSERT INTO Modules (name) VALUES ('%1')").arg(name))
//    return Utils.createDynamicObject(parent, "qrc:/qml/blocks/Module.qml", { arg: name })
    return Utils.createDynamicObject(parent, "qrc:/qml/nodes/Module.qml", { nodeId: id, arg: name, x: parent.width + 10 })
}

function addPrint(parent) {
    var name = "print"
    sproutDb.insertRecord(String("INSERT INTO Commands (name) VALUES ('%1')").arg(name))
//    return Utils.createDynamicObject(parent, "qrc:/qml/blocks/Print.qml", { arg: "text" })
    return Utils.createDynamicObject(parent, "qrc:/qml/nodes/Print.qml", { arg: "text", x: parent.width + 10 })
}

// ******************************** EDIT *************************************

function editModule(id, name) {
    sproutDb.updateRecord(String("UPDATE Modules SET name='%1' WHERE id='%2'").arg(name).arg(id))
}
