.import "../js/world.js" as World

var Ready = "Ready"
var Add = "Add"
var Edit = "Edit"
var Delete = "Delete"
var Go = "Go"
var Info = "Info"

function run(event) {
    if (commandState === Ready) {
        switch (event.text) {
            case "a": commandState = Add; break
            case "d": commandState = Delete; break
            case "e": commandState = Edit; break
            case "g": commandState = Go; break
            case "i": commandState = Info; break

            // move
            case "5": camera.position.z++; break // forward
            case "0": camera.position.z--; break // back
            case "4": camera.position.x++; camera.viewCenter.x++; break // left
            case "6": camera.position.x--; camera.viewCenter.x--; break // right
            case "8": camera.position.y++; camera.viewCenter.y++; break // up
            case "2": camera.position.y--; camera.viewCenter.y--; break // down

            case ".": camera.viewCenter = Qt.vector3d(0.0, 0.0, 0.0); break // view look at

        }
    } else if (commandState === Add) {
        switch (event.text) {
            case "m": currentUnit = World.addModule(currentUnit); commandState = Ready; break
            case "f": currentUnit = World.addFunction(currentUnit, currentUnit.unitId); commandState = Ready; break
            case "a": currentUnit = World.addArgument(currentUnit, currentUnit.unitId); commandState = Ready; break
            case "p": currentUnit = World.addPrintLine(currentUnit, currentUnit.unitId); commandState = Ready; break
            case "r": currentUnit = World.addReadLine(currentUnit, currentUnit.unitId); commandState = Ready; break
        }
    } else if (commandState === Delete) {
        switch (event.text) {
            case "y": currentUnit = World.deleteModule(currentUnit.unitId); commandState = Ready; break
            case "n": commandState = Ready; break
        }
    } else if (commandState === Edit) {
        switch (event.text) {

        }
    } else if (commandState === Go) {
        switch (event.text) {

        }
    } else if (commandState === Info) {
        switch (event.text) {

        }
    }
}
