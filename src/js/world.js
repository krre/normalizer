.import "../js/utils.js" as Utils

function createWorld() {
    addProject()
}

function lastId(table) {
    var module = sproutDb.readRecords(String("SELECT seq FROM sqlite_sequence WHERE name='%1'").arg(table))
    return module.length ? module[0].seq : 0
}

function addProject() {
    var record = sproutDb.readRecords("SELECT value FROM Defs WHERE name='project'")
    Utils.createDynamicObject(origin, "qrc:/qml/blocks/Project.qml", { arg: record[0].value })
}

function addModule() {
    var id = parseInt(lastId("Modules")) + 1
    var moduleName = "Module" + id
    sproutDb.insertRecord(String("INSERT INTO Modules (name) VALUES ('%1')").arg(moduleName))
    Utils.createDynamicObject(origin, "qrc:/qml/blocks/Module.qml", { arg: moduleName })
}

function addPrint() {
    var name = "Print"
    sproutDb.insertRecord(String("INSERT INTO Commands (name) VALUES ('%1')").arg(name))
    Utils.createDynamicObject(origin, "qrc:/qml/blocks/Print.qml", { arg: "Text" })
}
