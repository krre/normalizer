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
        }
    } else if (commandState === Add) {
        switch (event.text) {

        }
    } else if (commandState === Delete) {
        switch (event.text) {

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
