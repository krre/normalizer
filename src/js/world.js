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
    sproutDb.insertRecord("INSERT INTO Modules (name) VALUES ('module1')")
}
