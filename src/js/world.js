.import "../js/utils.js" as Utils

function createWorld() {
//    addFloor()
//    currentNode = addProject(origin)
    currentNode = addProject(scene2d)
    var moduleList = sproutDb.readRecords("SELECT * FROM Modules")
    for (var i in moduleList) {
        var module = moduleList[i]
        var moduleNode = Utils.createDynamicObject(currentNode, "qrc:/qml/nodes/Module.qml", { nodeId: module.id, arg: module.name, x: currentNode.width + 10, y: (currentNode.height + 10) * i })
    }

    currentNode = moduleNode

    var functionList = sproutDb.readRecords("SELECT * FROM Functions")
    for (i in functionList) {
        var func = functionList[i]
        var funcNode = Utils.createDynamicObject(currentNode, "qrc:/qml/nodes/Function.qml", { nodeId: func.id, arg: func.name, x: currentNode.width + 10, y: (currentNode.height + 10) * i })
    }

    currentNode = funcNode

    var instructionList = sproutDb.readRecords("SELECT * FROM Instructions")
    for (i in functionList) {
        var instr = instructionList[i]
        var instrNode = Utils.createDynamicObject(currentNode, "qrc:/qml/nodes/Instruction.qml", { nodeId: instr.id, arg: instr.name, x: currentNode.width + 10, y: (currentNode.height + 10) * i })
    }

    currentNode = instrNode

    var argumentList = sproutDb.readRecords("SELECT * FROM Arguments")
    for (i in argumentList) {
        var arg = argumentList[i]
        var argNode = Utils.createDynamicObject(currentNode, "qrc:/qml/nodes/Argument.qml", { nodeId: arg.id, arg: arg.arg, x: currentNode.width + 10, y: (currentNode.height + 10) * i })
    }

    currentNode = argNode
}

function lastId(table) {
    var module = sproutDb.readRecords(String("SELECT seq FROM sqlite_sequence WHERE name='%1'").arg(table))
    return module.length ? module[0].seq : 0
}

// ******************************** READ*************************************


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

function addFunction(parent, moduleId) {
    var id = parseInt(lastId("Functions")) + 1
    var name = "function" + id
    sproutDb.insertRecord(String("INSERT INTO Functions (name, moduleId) VALUES ('%1', %2)").arg(name).arg(moduleId))
    return Utils.createDynamicObject(parent, "qrc:/qml/nodes/Function.qml", { nodeId: id, arg: name, x: parent.width + 10 })
}

function addArgument(parent, instructionId) {
    var id = parseInt(lastId("Arguments")) + 1
    var arg = "arg" + id
    sproutDb.insertRecord(String("INSERT INTO Arguments (arg, instructionId) VALUES ('%1', %2)").arg(arg).arg(instructionId))
    return Utils.createDynamicObject(parent, "qrc:/qml/nodes/Argument.qml", { nodeId: id, arg: arg, x: parent.width + 10 })
}

function addPrintLine(parent, functionId) {
    var id = parseInt(lastId("Instructions")) + 1
    var name = "print-line"
    sproutDb.insertRecord(String("INSERT INTO Instructions (name, functionId) VALUES ('%1', %2)").arg(name).arg(functionId))
//    return Utils.createDynamicObject(parent, "qrc:/qml/blocks/Print.qml", { arg: arg })
    return Utils.createDynamicObject(parent, "qrc:/qml/nodes/Instruction.qml", { nodeId: id, arg: name, x: parent.width + 10 })
}

function addReadLine(parent, functionId) {
    var id = parseInt(lastId("Instructions")) + 1
    var name = "read-line"
    sproutDb.insertRecord(String("INSERT INTO Instructions (name, functionId) VALUES ('%1', %2)").arg(name).arg(functionId))
    return Utils.createDynamicObject(parent, "qrc:/qml/nodes/Instruction.qml", { nodeId: id, arg: name, x: parent.width + 10 })
}

// ******************************** EDIT *************************************

function editModule(id, name) {
    sproutDb.updateRecord(String("UPDATE Modules SET name='%1' WHERE id='%2'").arg(name).arg(id))
}

function editFunction(id, name) {
    sproutDb.updateRecord(String("UPDATE Functions SET name='%1' WHERE id='%2'").arg(name).arg(id))
}

function editArgument(id, arg) {
    sproutDb.updateRecord(String("UPDATE Arguments SET arg='%1' WHERE id='%2'").arg(arg).arg(id))
}

// ******************************** DELETE ************************************

function deleteModule(id) {
    sproutDb.deleteRecord(String("DELETE FROM Modules WHERE id=%1").arg(id))
    currentNode.destroy()
    currentNode = undefined
}
