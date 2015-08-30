.import "../js/utils.js" as Utils

function createWorld() {
    var list = sproutDb.readRecords("SELECT * FROM Defs")
    for (var i in list) {
        var record = list[i]
        if (record.name === "project") {
            Utils.createDynamicObject(origin, "qrc:/qml/blocks/Project.qml", { arg: record.value })
            break
        }
    }
}

function lastId(table) {
    var module = sproutDb.readRecords(String("SELECT seq FROM sqlite_sequence WHERE name='%1'").arg(table))
    return module.length ? module[0].seq : 0
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
