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

function addModule() {
    var id = parseInt(lastId("Modules")) + 1
    sproutDb.insertRecord(String("INSERT INTO Modules (name) VALUES ('%1')").arg("Module" + id))
}

function lastId(table) {
    var module = sproutDb.readRecords(String("SELECT seq FROM sqlite_sequence WHERE name='%1'").arg(table))
    return module[0].seq
}
