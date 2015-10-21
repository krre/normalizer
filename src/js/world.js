.import "../js/utils.js" as Utils

function createWorld(origin) {
    projectUnit = addProject(origin)

    var moduleList = sproutDb.readRecords("SELECT * FROM Modules")
    var radius = 0
    for (var i in moduleList) {
        var module = moduleList[i]
        var x = 0
        var y = -(i * radius * 2 + 0.07)
        var z = 0
        var moduleUnit = unitSet.module.createObject(projectUnit, { unitId: module.id, arg: module.name, position: Qt.vector3d(x, y, z)} )
        if (!radius) {
            radius = moduleUnit.pickForm.bound.radius
            moduleUnit.position = Qt.vector3d(x, y, z)
        }

        projectUnit.addChild(moduleUnit)
    }

/*
    var functionList = sproutDb.readRecords("SELECT * FROM Functions")
    for (i in functionList) {
        var func = functionList[i]
        var funcNode = Utils.createDynamicObject(undefined, "qrc:/qml/units/Function.qml", { unitId: func.id, arg: func.name, x: currentUnit.width + 10, y: (currentUnit.height + 10) * i })
    }

    var instructionList = sproutDb.readRecords("SELECT * FROM Instructions")
    for (i in functionList) {
        var instr = instructionList[i]
        var instrNode = Utils.createDynamicObject(undefined, "qrc:/qml/units/Instruction.qml", { unitId: instr.id, arg: instr.name, x: currentUnit.width + 10, y: (currentUnit.height + 10) * i })
    }

    var argumentList = sproutDb.readRecords("SELECT * FROM Arguments")
    for (i in argumentList) {
        var arg = argumentList[i]
        var argNode = Utils.createDynamicObject(undefined, "qrc:/qml/units/Argument.qml", { unitId: arg.id, arg: arg.arg, x: currentUnit.width + 10, y: (currentUnit.height + 10) * i })
    }
    */
}

function lastId(table) {
    var module = sproutDb.readRecords(String("SELECT seq FROM sqlite_sequence WHERE name='%1'").arg(table))
    return module.length ? module[0].seq : 0
}

// ******************************** READ*************************************


// ******************************** ADD *************************************

function addFloor() {
}

function addProject(parent) {
    var record = sproutDb.readRecords("SELECT value FROM Defs WHERE name='project'")
    var projectUnit = unitSet.project.createObject(undefined, { arg: record[0].value })
    parent.addChild(projectUnit)
    return projectUnit
}

function addModule(parent) {
    var id = parseInt(lastId("Modules")) + 1
    var name = "module" + id
    sproutDb.insertRecord(String("INSERT INTO Modules (name) VALUES ('%1')").arg(name))
    return Utils.createDynamicObject(parent, "qrc:/qml/units/Module.qml", { unitId: id, arg: name, position: Qt.vector3d(0, 0, parent.position.z + 0.1) })
}

function addFunction(parent, moduleId) {
    var id = parseInt(lastId("Functions")) + 1
    var name = "function" + id
    sproutDb.insertRecord(String("INSERT INTO Functions (name, moduleId) VALUES ('%1', %2)").arg(name).arg(moduleId))
    return Utils.createDynamicObject(parent, "qrc:/qml/units/Function.qml", { unitId: id, arg: name, position: Qt.vector3d(0, 0, parent.position.z + 0.1) })
}

function addArgument(parent, instructionId) {
    var id = parseInt(lastId("Arguments")) + 1
    var arg = "arg" + id
    sproutDb.insertRecord(String("INSERT INTO Arguments (arg, instructionId) VALUES ('%1', %2)").arg(arg).arg(instructionId))
    return Utils.createDynamicObject(parent, "qrc:/qml/units/Argument.qml", { unitId: id, arg: arg, position: Qt.vector3d(0, 0, parent.position.z + 0.1) })
}

function addPrintLine(parent, functionId) {
    var id = parseInt(lastId("Instructions")) + 1
    var name = "print-line"
    sproutDb.insertRecord(String("INSERT INTO Instructions (name, functionId) VALUES ('%1', %2)").arg(name).arg(functionId))
    return Utils.createDynamicObject(parent, "qrc:/qml/units/Instruction.qml", { unitId: id, arg: name, position: Qt.vector3d(0, 0, parent.position.z + 0.1) })
}

function addReadLine(parent, functionId) {
    var id = parseInt(lastId("Instructions")) + 1
    var name = "read-line"
    sproutDb.insertRecord(String("INSERT INTO Instructions (name, functionId) VALUES ('%1', %2)").arg(name).arg(functionId))
    return Utils.createDynamicObject(parent, "qrc:/qml/units/Instruction.qml", { unitId: id, arg: name, position: Qt.vector3d(0, 0, parent.position.z + 0.1) })
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
    currentUnit.getParentGroup().removeChild(currentUnit)
}
